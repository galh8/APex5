//
// Created by galhuta on 13/12/16.
//

#include "LuxuryCabFactory.h"
/**
 * @return new LuxuryCab
 */
TaxiCab *LuxuryCabFactory::create(int id, char manufacturer, char taxiColor) {
    return new LuxuryCab(id,manufacturer,taxiColor);
}

