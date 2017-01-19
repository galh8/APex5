//
// Created by amir on 02/12/16.
//

#ifndef EX2AP_DRIVER_H
#define EX2AP_DRIVER_H

#include "TripInfo.h"
#include "Node.h"
#include "DriverSatisfaction.h"
#include "TaxiCab.h"
#include <boost/serialization/access.hpp>
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


class Driver {
private:
    int driverID;
    int age;
    int yearsExperience;
    TripInfo *currentTrip;
    vector<Node*> tripRoute;
    char driverMartialStatus;
    DriverSatisfaction *averageSatisfaction;
    TaxiCab* taxiCabInfo;
    Node* driverLocation;
    bool occupied;
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) {

        ar & driverID;
        ar & age;
        ar & yearsExperience;
        ar & currentTrip;
        ar & driverMartialStatus;
        ar & averageSatisfaction;
        ar & taxiCabInfo;
        ar & driverLocation;
        ar & occupied;


    }

public:
    Driver(int driverId, int driverAge, char martialStat, int driverYearsOfExperience);
    Driver();
    ~Driver();
    int getID() const;
    int getYearsOfExperience() const;
    int getAge() const;
    int getAverageSatisfaction();
    char getMartialStatus();
    Node* getLocation();
    TaxiCab* getTaxiCabInfo();
    void setOccupied(bool occ);
    void setAge(int ageVal);
    void setYearsOfExperience(int years);
    void setMartialStatus(char status);
    void setAverageSatisfaction(int grade);
    void setTaxiCabInfo(TaxiCab* taxi);
    void setLocation(Node* locationVal);
    void setTripInfo(TripInfo *trip);
    bool operator==(const Driver &driver) const;
    bool isOccupied();
    TripInfo* getCurrentTrip();
    void move();

    vector<Node *> &getTripRoute();

    void setTripRoute(const vector<Node *> &tripRoute);

};

#endif //EX2AP_DRIVER_H
