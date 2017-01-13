//
// Created by galhuta on 14/12/16.
//

#include "TaxiFactory.h"
#include "StandardCabFactory.h"
#include "LuxuryCabFactory.h"

/**
 * setting the map of the factory.
 */
TaxiFactory::TaxiFactory() {

    factory_map[0] = new StandardCabFactory();
    factory_map[1] = new LuxuryCabFactory();
}

TaxiFactory::~TaxiFactory() {
    delete(factory_map[0]);
    delete(factory_map[1]);
}

/**
 * @param id - the id of the cab.
 * @param taxi_type - the type of the cab.
 * @param manufacturer  - the manufacturer of the cab.
 * @param taxiColor - the color of the cab.
 * @return - a new cab.
 */
TaxiCab* TaxiFactory::createTaxi(int id, int taxi_type, char manufacturer,
                                 char taxiColor) {
    TaxiCab* newTaxi = factory_map[taxi_type-1]->create(id, manufacturer,
                                                      taxiColor);
    return newTaxi;
}
