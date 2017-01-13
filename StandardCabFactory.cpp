//
// Created by galhuta on 13/12/16.
//

#include "StandardCabFactory.h"

/**
 * @return StandardCab.
 */
TaxiCab *StandardCabFactory::create(int id, char manufacturer, char taxiColor) {
    return new StandardCab(id,manufacturer,taxiColor);
}
