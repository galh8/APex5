//
// Created by amir on 02/12/16.
//

#include "TaxiCab.h"

/**
 * @return the cabId.
 */
int TaxiCab::getCabID() {
    return cabID;
}

/**
 * @return the cabId.
 */
double TaxiCab::getKilometersPassed() {
    return kilometersPassed;
}

/**
 * @return the cab manufacturer.
 */
carManufacturer TaxiCab::getCarManufacturer() {
    return manufacturer;
}

/**
 * @return the color of the cab.
 */
color TaxiCab::getColor() {
    return cabColor;
}

/**
 * the constructor.
 * @param id - the id of the cab.
 * @param cabManufacturer - the cab manufacturer.
 * @param colour - the color of the cab.
 */
TaxiCab::TaxiCab(int id, char cabManufacturer, char colour) {

    cabID = id;
    kilometersPassed = 0;

    /**
     * setting the manufacturer of the cab.
     */
    //TODO export that to a seperate function.
    switch (cabManufacturer) {
        case 'H':
            manufacturer = HONDA;
            break;
        case 'S':
            manufacturer = SUBARU;
            break;
        case 'T':
            manufacturer = TESLA;
            break;
        case 'F':
            manufacturer = FIAT;
            break;
        default:
            break;
    }

    /**
    * setting the color of the cab.
    */
    //TODO export that to a seperate function.
    switch (colour) {
        case 'R':
            cabColor = RED;
            break;
        case 'B':
            cabColor = BLUE;
            break;
        case 'G':
            cabColor = GREEN;
            break;
        case 'P':
            cabColor = PINK;
            break;
        case 'W':
            cabColor = WHITE;
            break;
        default:
            break;
    }
}

/**
 *
 * @param kmPassed
 */
void TaxiCab::updateKilometersPassed(double kmPassed) {
    kilometersPassed += kmPassed;
}

TaxiCab::TaxiCab() {

}

//double TaxiCab::getTariff() {
//    return tariff;
//}





