//
// Created by amir on 02/12/16.
//

#include "StandardCab.h"

/**
 *
 * @return - the step of each taxi.
 */
double StandardCab::getStepTurn() {
    return stepTurn;
}

/**
 * the constructor.
 * @param id - the id of the taxi.
 * @param manufacturer  - the manufacturer of the taxi.
 * @param colour - the color of the taxi.
 */
StandardCab::StandardCab(int id, char manufacturer,
                         char colour) : TaxiCab(id, manufacturer, colour) {
    stepTurn = 1;
    tariff = 1.0;
}

double StandardCab::getTariff()  {
    return tariff;
}

StandardCab::StandardCab() {

}





