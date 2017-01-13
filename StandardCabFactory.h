//
// Created by galhuta on 13/12/16.
//

#ifndef EX3_STANDARDCABCREATOR_H
#define EX3_STANDARDCABCREATOR_H


#include "TaxiFac.h"

class StandardCabFactory : public TaxiFac {
public:
    virtual TaxiCab* create(int id ,char manufacturer , char taxiColor);
};


#endif //EX3_STANDARDCABCREATOR_H
