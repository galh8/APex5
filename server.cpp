//
// Created by amir on 09/01/17.
//
#include <iostream>
#include "pthread.h"
#include "unistd.h"
#include "sockets/Socket.h"
#include "sockets/Tcp.h"
#include <netinet/in.h>
#include <map>
#include <queue>
#include "Driver.h"
#include "TaxiCenter.h"
#include "LuxuryCab.h"
#include "StandardCab.h"
#include "ClientThreadArgs.h"
//declerations:

//declerations:
std::map <int, pthread_t > sockThreads;
void* getNewClients(void* port);
void* insertDriverSendCab(void *clientSocketID);

BOOST_CLASS_EXPORT_GUID(LuxuryCab,"LuxuryCab")
BOOST_CLASS_EXPORT_GUID(GridNode,"GridNode")
BOOST_CLASS_EXPORT_GUID(StandardCab,"StandardCab")

int main(int argc,char* argv[]) {
    int sizeX, sizeY;
    int timePassed = 0;
    pthread_t clientsReceiver;
    int numOfObstacles, obs_x, obs_y;
    //vehicle variables
    int vehicleID, vehicleType;
    int driverID_toFind;
    char vehicleManufacturer, vehicleColor;
    //trip variables
    int tripID, tripStart_x, tripStart_y, tripEnd_x, tripEnd_y, tripNumPassengers, tripStartTime;
    double tripTariff;
    int command;
    char dummy;
    //The input
    cin >> sizeX;
    cin >> sizeY;
    //creating the taxi center with it's grid.
    TaxiCenter *taxiCenter = new TaxiCenter(sizeX, sizeY);


    cin >> numOfObstacles;
    //for loop for getting and setting the obstacles.
    for (int i = 0; i < numOfObstacles; i++) {
        cin >> obs_x;
        cin >> dummy;
        cin >> obs_y;
        taxiCenter->addMapObstacles(Point(obs_x, obs_y));
    }


    char buffer[1024];
    do {
        cin>>command;

        switch (command) {
            case 1: {
                int numberOfClients;
                cin >> numberOfClients;
                int port = atoi(argv[1]);
                ClientThreadArgs *cArgs = new ClientThreadArgs(taxiCenter, port, numberOfClients);
                int status = pthread_create(&clientsReceiver, NULL, getNewClients, (void *) cArgs);

                break;
            }


            case 2: {
                cin >> tripID;
                cin >> dummy;
                cin >> tripStart_x;
                cin >> dummy;
                cin >> tripStart_y;
                cin >> dummy;
                cin >> tripEnd_x;
                cin >> dummy;
                cin >> tripEnd_y;
                cin >> dummy;
                cin >> tripNumPassengers;
                cin >> dummy;
                cin >> tripTariff;
                cin >> dummy;
                cin >> tripStartTime;
                taxiCenter->receiveTripInfo(tripID, tripStart_x, tripStart_y, tripEnd_x,
                                            tripEnd_y, tripNumPassengers, tripTariff, tripStartTime);
                break;
            }

            case 3: {
                cin >> vehicleID;
                cin >> dummy;
                cin >> vehicleType;
                cin >> dummy;
                cin >> vehicleManufacturer;
                cin >> dummy;
                cin >> vehicleColor;
                taxiCenter->addTaxi(vehicleID, vehicleType, vehicleManufacturer, vehicleColor);
                break;
            }
            case 4: {
                //the id of the driver we want to find.
                cin >> driverID_toFind;
                cout << taxiCenter->getDriverLocation(driverID_toFind)->valueString() << endl;
                break;
            }
            case 7: {
                for(int i=0;i<taxiCenter->getDriversList().size(); i++) {
                    globalOperation[taxiCenter->getDriversList()[i]->getID()]->push(4);
                }
                case 9: {
                    taxiCenter->linkDriversTrips(timePassed);
                    taxiCenter->runAllTrips(timePassed);
                    ++timePassed;
                    break;
                }
            }





        }
    }while (command!=7);

    pthread_join(clientsReceiver,NULL);

}


//Main thread for receiving new client connections.
void* getNewClients(void* cArgs) {
    ClientThreadArgs *clientArgs = ((ClientThreadArgs*)cArgs);
    Socket *server = new Tcp(1, clientArgs->getServerPort());
    server->initialize();
    clientArgs->setSocket(server);
    int goodReception;
    int numberOfClients = clientArgs->getNumberOfClients();
//    cout << "Connection with " << server->getSocketDescriptor() << " established!" << endl;
    for(int i=0; i < numberOfClients ;++i) {
        goodReception= server->acceptClient();
        if (goodReception < 0) {
            //return an error represent error at this method
            cout << "Connection not established!" << endl;
        }else {
            pthread_t myThread;

            int status = pthread_create(&myThread, NULL, insertDriverSendCab, (void *) cArgs);
            if(status) {
                cout<<"ERROR! ";
            }
            sockThreads[clientArgs->getServer()->getSocketDescriptor()] = myThread ;
            pthread_join(myThread,NULL);
            //delete (clientArgs->getServer());
            //cout << "Connection with " << server->getSocketDescriptor() << " established!" << endl;
        }
    }
}

void* insertDriverSendCab(void *cArgs) {
    ClientThreadArgs *clientArgs = ((ClientThreadArgs*)cArgs);
    TaxiCenter *taxiCenter = clientArgs->getTaxiCenter();
    int driverVehicleID;
    Driver *driver;
    Socket *socket = clientArgs->getServer();
    char buffer[1024]="";
    char emptyBuffer[1024]="";

    //receive the serialized driver from the client.
    socket->reciveData(buffer, sizeof(buffer));

    usleep(1);
    string str2(buffer, sizeof(buffer));
    //Deserialize the driver received from the client.
    boost::iostreams::basic_array_source<char> device2(str2.c_str(), str2.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s3(device2);
    boost::archive::binary_iarchive ib(s3);
    ib >> driver;

    //receive the serialized vehicleID from the client.
    socket->reciveData(buffer, sizeof(buffer));
    usleep(1);
    driverVehicleID = atoi(buffer);
    //TODO lock this with mutex.
    globalOperation[driver->getID()] =new queue<int>;
    taxiCenter->addDriver(driver,driverVehicleID);
    cout << "the driver is "<<driver->getID()<<" added successfully to our station! "<<endl;

    Node* driverLocation = taxiCenter->getDriverLocation(driver->getID());
    //serialize the location of the driver on the grid.
    std::string serial_str3;
    boost::iostreams::back_insert_device<std::string> inserter7(serial_str3);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> >
            s4(inserter7);
    boost::archive::binary_oarchive o(s4);
    o << driverLocation;
    s4.flush();
    //sending the location
    socket->sendData(serial_str3);
    usleep(1);
    //serialize the info of the driver(the client).
    std::string serial_str1;
    TaxiCab *taxiCab = driver->getTaxiCabInfo();
    boost::iostreams::back_insert_device<std::string> inserter1(serial_str1);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> >
            s1(inserter1);
    boost::archive::binary_oarchive oa(s1);
    oa << taxiCab;
    s1.flush();
    //sending the cab
    socket->sendData(serial_str1);
    sleep(1);
    while (true) {
        if(globalOperation[driver->getID()]->size()!=0) {
//            cout<<"HALLELUYAH!" <<globalOperation[driver->getID()]->size()<<endl;
            int operToDo = globalOperation[driver->getID()]->front();
            globalOperation[driver->getID()]->pop();
            switch (operToDo) {
                case 1: {
                    socket->sendData(std::to_string(operToDo));
                    sleep(1);
                    //receiving the new location of the driver.
                    socket->reciveData(buffer, sizeof(buffer));
                    sleep(1);
                    string str(buffer, sizeof(buffer));
                    Node *newLocation;
                    boost::iostreams::basic_array_source<char> device1(str.c_str(),
                                                                       str.size());
                    boost::iostreams::stream<boost::iostreams::basic_array_source<char> >
                            s2(device1);
                    boost::archive::binary_iarchive ia(s2);
                    ia >> newLocation;
                    //Setting the new location of the driver.
                    driver->setLocation(newLocation);
                    if ((*((Point *) driver->getLocation()->getValue())) ==
                        *((Point *) (driver->getCurrentTrip()->getEndingPoint()->getValue()))) {
                        driver->setOccupied(false);
                        driver->setTripInfo(NULL);
                    }
                    break;
                }
                case 2: {
                    socket->sendData(std::to_string(operToDo));
                    sleep(1);
                    TripInfo *tripToSend = globalTripsMap[driver->getID()];

                    //serialize the trip info
                    std::string serial_str1;
                    boost::iostreams::back_insert_device<std::string> inserter1(serial_str1);
                    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> >
                            s1(inserter1);
                    boost::archive::binary_oarchive oa(s1);

                    oa << tripToSend;
                    s1.flush();
                    //sending the trip info
                    socket->sendData(serial_str1);
                    sleep(1);


                    break;
                }
            }
        }
    }


}

