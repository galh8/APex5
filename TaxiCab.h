//
// Created by amir on 02/12/16.
//

#ifndef EX2AP_TAXICAB_H
#define EX2AP_TAXICAB_H
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/serialization/access.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/archive/tmpdir.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>

#include <cmath>
#include <iostream>
enum color {RED,BLUE,GREEN,PINK,WHITE};
enum carManufacturer {HONDA,SUBARU,TESLA,FIAT};

class TaxiCab {
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & cabID;
        ar & manufacturer;
        ar & cabColor;
        ar & kilometersPassed;
        ar & tariff;

    }

protected:
    int cabID;
    carManufacturer manufacturer;
    color cabColor;
    double kilometersPassed;
    double tariff;
    carManufacturer getCarManufacturer();
    color getColor();


public:
    //TaxiCab(int id, carManufacturer manufacturer,color colour);
    TaxiCab(int id,char manufacturer,char colour);
    TaxiCab();
    void updateKilometersPassed(double kmPassed);
    double getKilometersPassed();
    virtual double getTariff()=0;
    int getCabID();
    virtual double getStepTurn() = 0;
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(TaxiCab)

#endif //EX2AP_TAXICAB_H
