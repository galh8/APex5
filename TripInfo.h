//
// Created by amir on 01/12/16.
//

#ifndef EX2AP_TRIPINFO_H
#define EX2AP_TRIPINFO_H


#include <cmath>
#include "Point.h"
#include "Node.h"
#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>


//#include "Driver.h"

class TripInfo {
private:
    int rideID;
    //Driver* tripDriver;
    double totalMeters;
    Node* startingPoint;
    Node* endingPoint;
    vector<Node*> tripRoute;
    int numOfPassengers;
    double tariff;
    int ratesReceived;
    int driverId;
    int timeOfTrip;
    bool firstTime;
public:
    bool IsAssigned() const;

    void setIsAssigned(bool isAssigned);

private:
    bool isAssigned;
public:
    bool isFirstTime();

    void setFirstTime(bool firstTime);

public:
    void setTripRoute(vector<Node *> &tripRoute);

private:
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & rideID;
        ar & totalMeters;
        ar & startingPoint;
        ar & endingPoint;
        ar & tripRoute;
        ar & numOfPassengers;
        ar & tariff;
        ar & ratesReceived;
        ar & driverId;
        ar & timeOfTrip;
    }
public:
    TripInfo(int driverId,Node *start, Node *dest, int currentNumOfPassengers,
             double currentTariff,int time);
    TripInfo();
    int getRideID();
    double getTotalMeters();
    void updateMeters(double meters);
    Node* getStartingPoint();
    Node* getEndingPoint();
    int getNumOfPassengers();
    double getTariff();
    void setTotalMeters(double meters);
    void setStartingPoint(Node* endingPoint);
    void setEndingPoint(Node* endingPoint);
    void setTariff(double tariff);
    vector<Node*> gettripRoute();
    int getDriverId();
    void setDriverId(int driverId);
    int getTimeOfTrip();
};


#endif //EX2AP_TRIPINFO_H
