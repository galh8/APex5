#include <iostream>
#include <unistd.h>
#include "Driver.h"
#include "Node.h"
#include "LuxuryCab.h"
#include "StandardCab.h"
#include "GridNode.h"
#include "sockets/Socket.h"
#include <string>
#include <unistd.h>
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

#include <boost/archive/tmpdir.hpp>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>
#include "sockets/Tcp.h"
#include "easylogging++.h"
#include "CheckArgs.h"

using namespace std;

BOOST_CLASS_EXPORT_GUID(LuxuryCab,"LuxuryCab")
BOOST_CLASS_EXPORT_GUID(GridNode,"GridNode")
BOOST_CLASS_EXPORT_GUID(StandardCab,"StandardCab")
_INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[])  {

    std::vector<std::string> argsAfterSeparation;
    string input;
    getline(std::cin, input);

    argsAfterSeparation = CheckArgs::checkClient(input);

    //checks if there is any problem with the client arguments. if there is
    // exiting the program.
    if (argsAfterSeparation.size() == 0) {
        LINFO<<"problem with client args, exiting program ";
        return 0;
    }

    Socket* client = new Tcp(0, atoi(argv[2]));
    //setting the desired ip address
    client->setIp_address(argv[1]);
    int dummyNum = 0;

    bool goodInput = false;
    client->initialize();

    //Dummy variable for getting the ',' and '_'
    char dummy;

    //Driver variables
    int driverID, driverAge, driverExperience;
    long long driverVehicleID;
    char driverStatus;

    //buffer of the data
    char buffer[42000] = "";
    char emptyBuffer[42000] = "";
    char emptyBuffer2[42000] = "";
    char dummyBuffer[42000] = "";
    long long dummyInteger = 1;
    //indicates if the drivers needs to move
    int serverOperation;





    //putting the input into the desired variables.
    driverID = stoi(argsAfterSeparation.at(0));
    driverAge = stoi(argsAfterSeparation.at(1));
    driverStatus = argsAfterSeparation.at(2)[0];
    driverExperience = stoi(argsAfterSeparation.at(3));
    driverVehicleID = stoi(argsAfterSeparation.at(4));

    //creating new driver
    Driver *driver = new Driver(driverID, driverAge, driverStatus,
                                driverExperience);

    //getting the dummy - needed in order to solve TCP problems
    client->reciveData(dummyBuffer, sizeof(dummyBuffer),dummyNum);
    //after receiving the dummy we can send our driver

    //serialize the info of the driver(the client).
    std::string serial_str1;
    boost::iostreams::back_insert_device<std::string> inserter1(serial_str1);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> >
            s1(inserter1);
    boost::archive::binary_oarchive oa(s1);
    oa << driver;
    s1.flush();

    //sending the driver
    client->sendData(serial_str1,dummyNum);

    LINFO<<"sending the driver " << driver->getID();

    //getting the dummy - needed in order to solve TCP problems
    client->reciveData(dummyBuffer, sizeof(dummyBuffer),dummyNum);
    //after receiving the dummy we can send our vehicleId

    //sending the vehicleID
    client->sendData(std::to_string(driverVehicleID),dummyNum);

    LINFO<<"sending the vehicleId " <<  driver->getID() << " and his vehicle id "
         << driverVehicleID;

    //expecting a location
    client->reciveData(emptyBuffer, sizeof(emptyBuffer),dummyNum);
    //receiving his location
    string str(emptyBuffer, sizeof(emptyBuffer));
    Node* location;
    boost::iostreams::basic_array_source<char> device(str.c_str(), str.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> >
            s(device);
    boost::archive::binary_iarchive i(s);
    i >> location;

    LINFO<<"Receiving the first location of the driver(supposed to be 0,0)";

    //set location
    driver->setLocation(location);
    //dummy send before receiving data(taxiCab object).
    client->sendData(std::to_string(dummyInteger),dummyNum);

    //expecting a taxi
    client->reciveData(emptyBuffer2, sizeof(emptyBuffer2),dummyNum);
    //receiving the taxi cab of the driver.
    string str1(emptyBuffer2, sizeof(emptyBuffer2));
    TaxiCab* taxiCab;
    boost::iostreams::basic_array_source<char> device1(str1.c_str(), str1.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> >
            s3(device1);
    boost::archive::binary_iarchive ia(s3);
    ia >> taxiCab;

    LINFO<<"Receiving the taxi cab of the driver : " << driver->getID();

    //setting the taxi to the driver.
    driver->setTaxiCabInfo(taxiCab);

    /**
 * loop that reicives 1 or 2.
 * 1 - move the driver.
 * 2 - get new trip.
 * 3 - do nothing.
 * 4 - exit.(realise memory).
 */
    while (true){
        //dummy send before receiving data(serverOperation).
        client->sendData(std::to_string(dummyInteger),dummyNum);

        //reicives a command to server operation variable.
        client->reciveData(buffer, sizeof(buffer),dummyNum);
        serverOperation = atoi(buffer);

        // 1 means - move!
        if (serverOperation == 1) {
            //checks that there is a trip
            if (driver->getCurrentTrip() != NULL) {
                //checks if the trip route is larger than 1
                if (driver->getCurrentTrip()->gettripRoute().size() != 0) {
                    driver->move();
                    Node *driverLocation = driver->getLocation();
                    //serialize the location of the driver.
                    std::string serial_str3;
                    boost::iostreams::back_insert_device<std::string> inserter3(
                            serial_str3);
                    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> >
                            s6(inserter3);
                    boost::archive::binary_oarchive ob(s6);
                    ob << driverLocation;
                    s6.flush();
                    //sending the location of the driver after moving
                    client->sendData(serial_str3,dummyNum);

                    LINFO<<"driver : " << driver->getID() << "send his new location"
                         << driverLocation->valueString();

                }else {
                    delete(driver->getCurrentTrip());
                    int routeSize = driver->getTripRoute().size();
                    for(int j=0;j<routeSize;j++){
                        delete(driver->getTripRoute()[j]);
                    }
                    driver->setOccupied(false);
                    driver->setTripInfo(NULL);
                }
            }
            //if server operation = 2 the program expecting to get new trip
        } else if(serverOperation==2) { //we need to set a new trip info.
            //dummy send before receiving data(tripInfo).
            client->sendData(std::to_string(dummyInteger),dummyNum);

            //expecting a tripInfo.
            client->reciveData(buffer, sizeof(buffer),dummyNum);

            string str2(buffer, sizeof(buffer));
            TripInfo* tripInfo;
            boost::iostreams::basic_array_source<char> device2(str2.c_str(), str2.size());
            boost::iostreams::stream<boost::iostreams::basic_array_source<char> >
                    s4(device2);
            boost::archive::binary_iarchive ib(s4);
            ib >> tripInfo;

            LINFO<<"driver : " << driver->getID() << " got trip num : " << tripInfo->getRideID();

            //assigning the trip to the driver.
            if(tripInfo != NULL){
                driver->setOccupied(true);
                //setting trip info to the driver.
                driver->setTripInfo(tripInfo);
                driver->setTripRoute(tripInfo->gettripRoute());
            }

        }else if(serverOperation == 4) {
           //deletes everything and exit client.
            LINFO<<"deleting driver num : " << driver->getID();
            delete(client);
            delete(driver->getTaxiCabInfo());
            delete(driver);
            return 0;
        }

    }

}