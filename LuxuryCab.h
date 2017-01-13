//
// Created by amir on 02/12/16.
//

#ifndef EX2AP_LUXURYCAB_H
#define EX2AP_LUXURYCAB_H
#include "TaxiCab.h"



class LuxuryCab: public TaxiCab {
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
    LuxuryCab(int id, char manufacturer,char colour);
    LuxuryCab();
    double getStepTurn();

};



#endif //EX2AP_LUXURYCAB_H
