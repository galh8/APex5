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
#include <mutex>
#include "easylogging++.h"
#include "CheckArgs.h"
std::mutex mtx;           // mutex for critical section




//declerations:
void* getNewClients(void* port);
void* clientThread(void *clientSocketID);

BOOST_CLASS_EXPORT_GUID(LuxuryCab,"LuxuryCab")
BOOST_CLASS_EXPORT_GUID(GridNode,"GridNode")
BOOST_CLASS_EXPORT_GUID(StandardCab,"StandardCab")
_INITIALIZE_EASYLOGGINGPP

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
    string input;
    bool goodInputOfGridAndObs = false;
    bool goodObsInput = true;
    int i;
    std::vector<std::string> GridArgsAfterSeparation;
    std::vector<Point> ObstaclesBeforeAdding;

    //getting input of the grid and the obstacles.
    while (!(goodInputOfGridAndObs)) {
        getline(std::cin, input);

        GridArgsAfterSeparation = CheckArgs::checkGridArguments(input);

        if (GridArgsAfterSeparation.size() == 0) {
            LINFO<<"problem with grid args, need to type all args again ";
            cout <<"-1"<<endl;
            GridArgsAfterSeparation.clear();
            continue;
        }

        getline(std::cin, input);

        if (!(CheckArgs::isNonNegativeInteger(input))) {
            LINFO<<"problem with number of obs args, need to type all args again ";
            cout <<"-1"<<endl;
            GridArgsAfterSeparation.clear();
            continue;
        }

        numOfObstacles = stoi(input);

        //getting all the obstacles
        for (i = 0; i < numOfObstacles; i++) {
            getline(std::cin, input);
            std::vector<std::string> ObsArgsAfterSeparation = CheckArgs::checkObstacleArguments(input);
            if (ObsArgsAfterSeparation.size() == 0) {
                goodObsInput = false;
                LINFO<<"problem with obs args, need to type all args again ";
                cout <<"-1"<<endl;
                break;
            }
            ObstaclesBeforeAdding.push_back(Point(stoi(ObsArgsAfterSeparation.at(0)),stoi(ObsArgsAfterSeparation.at(1))));
        }

        if (!(goodObsInput)) {
            goodObsInput = true;
            ObstaclesBeforeAdding.clear();
            GridArgsAfterSeparation.clear();
            continue;
        }

        goodInputOfGridAndObs = true;

    }

    //creating the taxi center with it's grid.
    TaxiCenter *taxiCenter = new TaxiCenter(stoi(GridArgsAfterSeparation.at(0)),
                                            stoi(GridArgsAfterSeparation.at(1)));

    for (i = 0; i < ObstaclesBeforeAdding.size(); i++) {
        taxiCenter->addMapObstacles(ObstaclesBeforeAdding.at(i));
    }


    //initializing the server
    int port = atoi(argv[1]);
    Socket *server = new Tcp(1,port);
    //defining ClientThreadArgs
    ClientThreadArgs *cArgs;



    char buffer[1024];
    do {
        bool goodCommandInput = false;
        while (!(goodCommandInput)) {
            getline(std::cin, input);

            if (!(CheckArgs::isNonNegativeInteger(input))) {
                LINFO << "problem with command number ";
                cout <<"-1"<<endl;
                continue;
            }
            goodCommandInput = true;
        }

        command = stoi(input);

        switch (command) {
            case 1: {
                bool goodClientsNumInput = false;
                while (!(goodClientsNumInput)) {
                    getline(std::cin, input);

                    if (!(CheckArgs::isNonNegativeInteger(input))) {
                        LINFO << "problem with number of clients  ";
                        cout <<"-1"<<endl;
                        continue;
                    }
                    goodClientsNumInput = true;
                }
                int numberOfClients = stoi(input);
                cArgs = new ClientThreadArgs(taxiCenter, server,numberOfClients);
                LINFO<<"Creating the thread for getting new clients! ";
                int status = pthread_create(&clientsReceiver, NULL, getNewClients, (void *) cArgs);
                pthread_join(clientsReceiver,NULL);
                LINFO<<"Finished to accept clients, waiting for receiving all the drivers! ";
                while (true) {
                    if(numberOfClients==taxiCenter->getDriversList().size()) {
                        break;
                    }
                }
                break;
            }
            case 2: {
                mtx.lock();
                std::vector<std::string> TripArgsAfterSeparation;
                string tripInput;
                getline(std::cin, tripInput);
                cout<<tripInput<<endl;
                TripArgsAfterSeparation = CheckArgs::checkTripInfoArguments(tripInput);
                if (TripArgsAfterSeparation.size() == 0) {
                    LINFO<<"problem with trip args arguments ";
                    cout <<"-1"<<endl;
                    mtx.unlock();
                    break;
                }

                //putting the input into the desired variables.
                tripID = stoi(TripArgsAfterSeparation.at(0));

                tripStart_x = stoi(TripArgsAfterSeparation.at(1));
                tripStart_y = stoi(TripArgsAfterSeparation.at(2));
                tripEnd_x = stoi(TripArgsAfterSeparation.at(3));
                tripEnd_y = stoi(TripArgsAfterSeparation.at(4));
                tripNumPassengers = stoi(TripArgsAfterSeparation.at(5));
                tripTariff = stoi(TripArgsAfterSeparation.at(6));
                tripStartTime = stoi(TripArgsAfterSeparation.at(7));

                taxiCenter->receiveTripInfo(tripID, tripStart_x, tripStart_y, tripEnd_x,
                                            tripEnd_y, tripNumPassengers, tripTariff, tripStartTime);
                mtx.unlock();
                break;
            }
            case 3: {
                mtx.lock();

                std::vector<std::string> TaxiCabArgsAfterSeparation;
                string tripInput;


                getline(std::cin, tripInput);

                TaxiCabArgsAfterSeparation = CheckArgs::checkTaxiArguments(tripInput);

                if (TaxiCabArgsAfterSeparation.size() == 0) {
                    LINFO<<"problem with taxi args arguments ";
                    cout <<"-1"<<endl;
                    mtx.unlock();
                    break;
                }

                //putting the input into the desired variables.
                vehicleID = stoi(TaxiCabArgsAfterSeparation.at(0));
                vehicleType = stoi(TaxiCabArgsAfterSeparation.at(1));
                vehicleManufacturer = TaxiCabArgsAfterSeparation.at(2)[0];
                vehicleColor = TaxiCabArgsAfterSeparation.at(3)[0];

                taxiCenter->addTaxi(vehicleID, vehicleType, vehicleManufacturer, vehicleColor);
                mtx.unlock();
                break;
            }
            case 4: {
                //the id of the driver we want to find.
                    getline(std::cin, input);

                    if (!(CheckArgs::isNonNegativeInteger(input))) {
                        LINFO << "problem with number of clients  ";
                        cout<<"-1"<<endl;
                        break;
                    }
                driverID_toFind = stoi(input);
                LINFO<<"Waiting that the driver will finish all his steps before printing his location. ";
                //printing the driver location just when the driver finished to move
                while (true) {
                    if(taxiCenter->getDriverLocation(driverID_toFind) == NULL) {
                        cout <<"-1"<<endl;
                        break;
                    }else if ((globalOperation[driverID_toFind]->size() == 0)) {
                        cout << taxiCenter->getDriverLocation(driverID_toFind)->valueString() << endl;
                        break;
                    }
                }
                break;
            }
            case 7: {
                mtx.lock();
                LINFO<<"Send the thread a sign that the program finishing. ";
                for (int i = 0; i < taxiCenter->getDriversList().size(); i++) {
                    globalOperation[taxiCenter->getDriversList()[i]->getID()]->push(4);
                }
                mtx.unlock();

                bool everyClientFinished = false;
                LINFO<<"Waiting for all the clients to finish their work ";
                while(!everyClientFinished){
                    everyClientFinished = true;
                    for(int i=0;i< globalOperation.size(); i++) {
                        if (globalOperation.at(i)->size() != 0){
                            everyClientFinished = false;
                            break;
                        }
                    }
                }
                LINFO<<"All the clients finished their work. starting to free memory. ";
                //frees everything
                taxiCenter->getBfsPool()->terminate();
                //deletes the taxiCenter.
                delete(taxiCenter);
                LINFO<<"Texi center released successfuly ";
                //deletes the server.
                delete(server);
                LINFO<<"server released successfuly ";
                //deletes clientArgs.
                delete(cArgs);
                LINFO<<"cArgs released successfuly ";
                for(int i=0;i<globalOperation.size();i++){
                    queue<int> *queueToDel = globalOperation.at(i);
                    delete(queueToDel);
                }
                LINFO<<"All the queues released successfuly from the global map ";
                LINFO<<"All the memory released ";
                return 0;
            }
            case 9: {
                mtx.lock();
                LINFO<<"Start linking trips to drivers. ";
                taxiCenter->linkDriversTrips(timePassed);
                LINFO<<"Finished link trips to drivers.";
                LINFO<<"Start running all the trips. ";
                taxiCenter->runAllTrips(timePassed);
                mtx.unlock();
                ++timePassed;
                bool everyClientFinished = false;
                while(!everyClientFinished){
                    everyClientFinished = true;
                    for(int i=0;i< globalOperation.size(); i++) {
                        if (globalOperation.at(i)->size() != 0){
                            everyClientFinished = false;
                            break;
                        }
                    }
                }
                LINFO<<"All the trips finished to run (also in client) ";
                break;
            }

            default:{
                break;
            }
        }

    }while (command!=7);


}


//Main thread for receiving new client connections.
void* getNewClients(void* cArgs) {
    ClientThreadArgs *clientArgs = ((ClientThreadArgs*)cArgs);
    Socket *server = clientArgs->getServer();
    int numberOfClients = clientArgs->getNumberOfClients();
    server->initialize();
    LINFO<<"Server socket initialized ";
    clientArgs->setServer(server);
    int goodReception;
    for(int i=0; i<numberOfClients ;++i) {
        goodReception= server->acceptOneClient();

        //clones the original ClientThreadArgs and set a new socketDescriptor.
        if (goodReception < 0) {
            //return an error represent error at this method
            cout << "Connection not established!" << endl;
        }else {
            pthread_t myThread;
            ClientThreadArgs *newClient = new ClientThreadArgs(clientArgs,goodReception);
            int status = pthread_create(&myThread, NULL, clientThread, (void *) newClient);
            if(status) {
                cout<<"ERROR! ";
            }
            LINFO<<"The thread of the client "<<i+1<<"  created successfuly!";
        }
    }

}

void* clientThread(void *cArgs) {

    ClientThreadArgs *clientArgs = ((ClientThreadArgs*)cArgs);

    TaxiCenter *taxiCenter = clientArgs->getTaxiCenter();
    int driverVehicleID;
    //while keepMovin is true the client is still in the game.
    bool keepMovin = true;
    Driver *driver;
    Socket *server = clientArgs->getServer();
    int socketDes = clientArgs->getSocketDes();
    LINFO<<"The thread of the client "<<socketDes<<"  (socket descriptor) started !";
    char buffer[13000]="";
    char emptyBuffer[13000]="";
    char dummyBuffer[100]= "";
    long long dummyInteger = 1;

    //dummy send before receiving data(driver object).
    server->sendData(std::to_string(dummyInteger),socketDes);

    //receive the serialized driver from the client.
    server->reciveData(buffer, sizeof(buffer),socketDes);
    string str2(buffer, sizeof(buffer));
    //Deserialize the driver received from the client.
    boost::iostreams::basic_array_source<char> device2(str2.c_str(), str2.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s3(device2);
    boost::archive::binary_iarchive ib(s3);
    ib >> driver;
    LINFO<<"The serialized driver received successfuly, his ID is "<<driver->getID();
    //dummy send before receiving data(vehicleID object).
    server->sendData(std::to_string(dummyInteger),socketDes);

    //receive the serialized vehicleID from the client.
    server->reciveData(buffer, sizeof(buffer),socketDes);
    driverVehicleID = atoi(buffer);
    LINFO<<"The vehicle ID received from client is: "<<driverVehicleID;
    globalOperation[driver->getID()] =new queue<int>;
    LINFO<<"The global map of driver "<<driver->getID()<<" Initialized!";
    mtx.lock();
    taxiCenter->addDriver(driver,driverVehicleID);

    Node* driverLocation = taxiCenter->getDriverLocation(driver->getID());
    mtx.unlock();
    //serialize the location of the driver on the grid.
    std::string serial_str3;
    boost::iostreams::back_insert_device<std::string> inserter7(serial_str3);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> >
            s4(inserter7);
    boost::archive::binary_oarchive o(s4);
    o << driverLocation;
    s4.flush();
    //sending the location
    server->sendData(serial_str3,socketDes);
    LINFO<<"The first location sent ["<<driverLocation->valueString()<<"]";


    //getting the dummy - needed in order to solve TCP problems
    server->reciveData(dummyBuffer, sizeof(dummyBuffer),socketDes);
    //after receiving the dummy we can send our taxiCab

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
    server->sendData(serial_str1,socketDes);
    LINFO<<"The cab "<<taxiCab->getCabID()<<" sent to driver "<<driver->getID();
    LINFO<<"Infinite while of thread (of driverID "<<driver->getID()<<") started...";
    while (keepMovin) {
        if(globalOperation[driver->getID()]->size()!=0) {
            long long operToDo = globalOperation[driver->getID()]->front();
            switch (operToDo) {
                case 1: {
                    //getting the dummy - needed in order to solve TCP problems
                    server->reciveData(dummyBuffer, sizeof(dummyBuffer),socketDes);
                    //after receiving the dummy we can send the operToDo
                    //sends the client what to do
                    server->sendData(std::to_string(operToDo),socketDes);
                    LINFO<<"The operation "<<operToDo<<" sent to client (DriverID "<<driver->getID()<<")";
                    //receiving the new location of the driver.
                    server->reciveData(buffer, sizeof(buffer),socketDes);
                    string str(buffer, sizeof(buffer));
                    Node *newLocation;
                    boost::iostreams::basic_array_source<char> device1(str.c_str(),
                                                                       str.size());
                    boost::iostreams::stream<boost::iostreams::basic_array_source<char> >
                            s2(device1);
                    boost::archive::binary_iarchive ia(s2);
                    ia >> newLocation;
                    //Setting the new location of the driver.
                    mtx.lock();
                    LINFO<<"The new location of driver "<<driver->getID()<< " is "<< newLocation->valueString();
                    Point newPoint = (*((Point *) newLocation->getValue()));
                    driver->setLocation(taxiCenter->getMap()->getGridNode(newPoint));

                    delete(newLocation);
                    LINFO<<"The temp location deleted successfully!";
                    if ((*((Point *) driver->getLocation()->getValue())) ==
                        *((Point *) (driver->getCurrentTrip()->getEndingPoint()->getValue()))) {
                        LINFO<<"The driver "<<driver->getID()<< " arrived to his destination";
                        driver->setOccupied(false);
                        driver->setTripInfo(NULL);
                    }
                    globalOperation[driver->getID()]->pop();
                    mtx.unlock();
                    break;
                }
                case 2: {
                    //getting the dummy - needed in order to solve TCP problems
                    server->reciveData(dummyBuffer, sizeof(dummyBuffer),socketDes);
                    //after receiving the dummy we can send the operToDo

                    //sends the client what to do
                    server->sendData(std::to_string(operToDo),socketDes);
                    LINFO<<"The operation "<<operToDo<<" sent to client (DriverID "<<driver->getID()<<")";
                    //getting the dummy - needed in order to solve TCP problems
                    server->reciveData(dummyBuffer, sizeof(dummyBuffer),socketDes);
                    //after receiving the dummy we can send the tripToSend
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
                    server->sendData(serial_str1,socketDes);
                    LINFO<<"The trip from "<<tripToSend->getStartingPoint()->valueString() <<
                                               " to "<<tripToSend->getEndingPoint()->valueString()<<" sent to driver "<<
                            driver->getID();
                    mtx.lock();
                    globalOperation[driver->getID()]->pop();
                    mtx.unlock();
                    break;
                }

                case 4: {
                    //getting the dummy - needed in order to solve TCP problems
                    server->reciveData(dummyBuffer, sizeof(dummyBuffer),socketDes);
                    //after receiving the dummy we can send the operToDo

                    //sends the client what to do
                    server->sendData(std::to_string(operToDo),socketDes);
                    LINFO<<"The operation "<<operToDo<<" sent to client (DriverID "<<driver->getID()<<")";


                    //deleting the clientsArgs of this specific client.
                    delete(clientArgs);
                    LINFO<<"Client args released.";
                    mtx.lock();
                    globalOperation[driver->getID()]->pop();
                    mtx.unlock();

                    //terminate the thread
                    keepMovin = false;
                }
            }
        }
    }
}

