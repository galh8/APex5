//
// Created by amir on 02/12/16.
//

#ifndef EX2AP_TAXICENTER_H
#define EX2AP_TAXICENTER_H

#include "Grid.h"
#include <vector>
#include "Driver.h"
#include "TaxiCab.h"
#include "TripInfo.h"
#include "Node.h"
#include "Passenger.h"
#include "sockets/Socket.h"
#include "sockets/Tcp.h"
#include <map>
#include <queue>

//The global variable containing the trips.
extern map<int,TripInfo*> globalTripsMap;
//The global variable containing the operations client should do.
extern map<int, queue<int>* > globalOperation;

class TaxiCenter {
private:
    Grid *map;
    vector<Driver*> driversList;
    vector<TaxiCab*> taxisList;
    vector<TripInfo*> listOfTrips;
    void sendTaxi(Node* location);

public:
    vector<Driver *> &getDriversList();

    TaxiCenter(int rows,int columns);

    ~TaxiCenter();

    Grid *getMap();

    vector<TripInfo*> &getListOfTrips();

    const vector<TaxiCab*> &getTaxisList() const;

//    void receiveCallOrder(string callOrder);

    Node* getDriverLocation(int driverID);

    void addDriver(Driver* driver,int taxiId);

    void addTaxi(int id,int taxi_type
            ,char manufacturer,char taxiColor);

    void receiveTripInfo(int tripId, int xStart, int yStart, int xEnd, int yEnd,
                         int numPassengers, double tariff,int timeOfTrip);

    void setDriversList(const vector<Driver> &driversList);

    Driver* findClosestDriver(TripInfo* tripInfo);

    void linkDriversTrips(int currentTime);

    void runAllTrips(int currentTime);

    void addMapObstacles(Point obsPoint);

};


#endif //EX2AP_TAXICENTER_H
