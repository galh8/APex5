//
// Created by amir on 02/12/16.
//

#include "Driver.h"
#include "Node.h"
#include <stdio.h>

/**
 * The constructor.
 * @param driverId - the id of the driver.
 * @param driverAge - the age of the driver.
 * @param martialStat - the martial status of the driver.
 * @param driverYearsOfExperience - years of experience of the driver.
 * @param vehicleID - the id of the vehicle.
 */
Driver::Driver(int driverId, int driverAge,char martialStat,
               int driverYearsOfExperience) {
    driverID = driverId;
    currentTrip = NULL;
    age = driverAge;
    averageSatisfaction = new DriverSatisfaction();
    yearsExperience = driverYearsOfExperience;
    driverMartialStatus = martialStat;
    occupied = false;
    driverLocation = NULL;
    taxiCabInfo = NULL;

}

Driver::Driver() {

}

/**
 * The destructor.
 */
Driver::~Driver() {
    delete(averageSatisfaction);
//    if (driverLocation != NULL) {
//        delete(driverLocation);
//        driverLocation=NULL;
//    }

}

/**
 * @return the id of the driver.
 */
int Driver::getID() const {
    return driverID;
}

/**
 * @return the years of experience of the driver.
 */
int Driver::getYearsOfExperience() const {
    return yearsExperience;
}

/**
 * @return the age of the driver.
 */
int Driver::getAge() const {
    return age;
}

/**
 * @return the avarege satisfaction of the driver.
 */
int Driver::getAverageSatisfaction() {
    return averageSatisfaction->getSatisfaction();
}

/**
 * @return the martial status of the driver.
 */
char Driver::getMartialStatus() {
    return driverMartialStatus;
}

/**
 * @return the location of the driver
 */
Node *Driver::getLocation() {
    return driverLocation;
}

/**
 * set the age of the driver.
 * @param ageVal - the age of the driver.
 */
void Driver::setAge(int ageVal) {
    age = ageVal;
}

/**
 * set years of experience.
 * @param years - the years of experience of the driver.
 */
void Driver::setYearsOfExperience(int years) {
    yearsExperience = years;
}

/**
 * set the martial status of the driver.
 * @param martialStatus the martial status of the driver.
 */
void Driver::setMartialStatus(char martialStatus) {
    driverMartialStatus = martialStatus;
}

/**
 * @param grade - the grade that  was given to the driver.
 */
void Driver::setAverageSatisfaction(int grade) {
    averageSatisfaction->updateSatisfaction(grade);
}

/**
 *  set the location of the driver.
 * @param locationVal - the location of the driver.
 */
void Driver::setLocation(Node *locationVal) {
    driverLocation = locationVal;
}

/**
 * @param driver - the driver we want to compare with
 * @return bool of the comparation
 */
bool Driver::operator==(const Driver &driver) const {
    return driverID == driver.getID();
}

/**
 * @return the taxiCabInfo.1
 */
TaxiCab* Driver::getTaxiCabInfo() {
    return taxiCabInfo;
}

/**
 * set the taxi of the driver.
 * @param taxi - the taxi of the driver.
 */
void Driver::setTaxiCabInfo(TaxiCab* taxi) {
    taxiCabInfo = taxi;
}

/**
 * set if the driver is occupied or not.
 * @param occ - the occupation status of the driver.
 */
void Driver::setOccupied(bool occ) {
    occupied = occ;
}

/**
 * @return if the driver is occupied or not.
 */
bool Driver::isOccupied() {
    return occupied;
}

/**
 * @return the currentTrip.
 */
TripInfo* Driver::getCurrentTrip() {
    return currentTrip;
}

/**
 * set the trip for the driver.
 * @param trip - the trip the driver supposed to do.
 */
void Driver::setTripInfo(TripInfo *trip) {
        currentTrip = trip;

}


void Driver::move() {
    vector<Node*> tripRoute = getCurrentTrip()->gettripRoute();
    double stepTurn = taxiCabInfo->getStepTurn();
    if (getCurrentTrip() != NULL) {
        //move as many times as the taxi allows
        if (tripRoute.size() == 2) {
            setLocation(tripRoute[1]);
            getCurrentTrip()->setTotalMeters(1);
            getTaxiCabInfo()->updateKilometersPassed(1);
            tripRoute.erase(tripRoute.begin());

            //set the driver to be unOccupied
            setTripInfo(NULL);
            setOccupied(false);

        }else if (tripRoute.size() > 1) {
            setLocation(tripRoute[stepTurn]);
            getCurrentTrip()->setTotalMeters(stepTurn);
            getTaxiCabInfo()->updateKilometersPassed(stepTurn);
            tripRoute.erase(tripRoute.begin(), tripRoute.begin()+stepTurn);
            currentTrip->setTripRoute(tripRoute);

        } else {
            setLocation(tripRoute[stepTurn-1]);
            getCurrentTrip()->setTotalMeters(stepTurn-1);
            getTaxiCabInfo()->updateKilometersPassed(stepTurn-1);
            tripRoute.erase(tripRoute.begin() , tripRoute.begin()+stepTurn -1);
            currentTrip->setTripRoute(tripRoute);

            //set the driver to be unOccupied
            setTripInfo(NULL);
            setOccupied(false);
        }
    }


}

vector<Node *> &Driver::getTripRoute() {
    return tripRoute;
}

void Driver::setTripRoute(const vector<Node *> &tripRoute) {
    Driver::tripRoute = tripRoute;
}


