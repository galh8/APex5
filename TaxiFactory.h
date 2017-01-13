//
// Created by galhuta on 14/12/16.
//

#ifndef EX3_TAXIFACTORY_H
#define EX3_TAXIFACTORY_H

#include "TaxiFac.h"
#include <map>

class TaxiFactory {
private:
    std::map<int, TaxiFac*>  factory_map;
public:
    TaxiFactory();
    ~TaxiFactory();
    TaxiCab* createTaxi(int id, int taxi_type, char manufacturer,
                                  char taxiColor);
};



#endif //EX3_TAXIFACTORY_H
