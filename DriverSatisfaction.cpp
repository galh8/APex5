//
// Created by amir on 02/12/16.
//

#include "DriverSatisfaction.h"

/**
 * the constructor.
 */
DriverSatisfaction::DriverSatisfaction() {
    averageSatisfaction = 0;
    numOfTrips = 0;
}

/**
 * update the avrage satisfaction of the driver.
 * @param satisfaction - satisfaction from one passenger.
 */
void DriverSatisfaction::updateSatisfaction(int satisfaction) {
    int sumSatisfaction;
    sumSatisfaction = (averageSatisfaction*numOfTrips);
    sumSatisfaction += satisfaction;
    numOfTrips++;
    averageSatisfaction = sumSatisfaction/numOfTrips;
}

/**
 * @return the number of trips of the driver.
 */
int DriverSatisfaction::getNumOfTrips() {
    return numOfTrips;
}

/**
 * @return - the satisfaction from the driver.
 */
int DriverSatisfaction::getSatisfaction() {
    return averageSatisfaction;
}

