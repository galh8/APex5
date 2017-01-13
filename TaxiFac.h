//
// Created by galhuta on 13/12/16.
//

#ifndef EX3_TAXIFAC_H
#define EX3_TAXIFAC_H


#include <map>
#include "TaxiCab.h"
#include "StandardCab.h"
#include "LuxuryCab.h"

class TaxiFac {
public:
    virtual TaxiCab *create(int id, char manufacturer, char color) = 0;
};

#endif //EX3_TAXIFACTORY_H
