//
// Created by amir on 02/12/16.
//

#ifndef EX2AP_STANDARDCAB_H
#define EX2AP_STANDARDCAB_H

#include "TaxiCab.h"


class StandardCab:public TaxiCab{
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & boost::serialization::base_object<TaxiCab>(*this);
        ar & stepTurn;
        ar & tariff;
    }
private:
    int stepTurn;
    double tariff;

public:
    double getTariff();

public:
    StandardCab(int id, char manufacturer,char colour);
    StandardCab();
    double getStepTurn();
};




#endif //EX2AP_STANDARDCAB_H
