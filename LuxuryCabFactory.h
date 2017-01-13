//
// Created by galhuta on 13/12/16.
//

#ifndef EX3_LUXURYCABCREATOR_H
#define EX3_LUXURYCABCREATOR_H


#include "TaxiFac.h"

class LuxuryCabFactory : public TaxiFac {
public:
    virtual TaxiCab* create(int id ,char manufacturer , char taxiColor);
};


#endif //EX3_LUXURYCABCREATOR_H
