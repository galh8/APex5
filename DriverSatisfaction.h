//
// Created by amir on 02/12/16.
//

#ifndef EX2AP_DRIVERSATISFACTION_H
#define EX2AP_DRIVERSATISFACTION_H
#include <boost/serialization/access.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
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



class DriverSatisfaction {
private:
    int numOfTrips;
    int averageSatisfaction;
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & numOfTrips;
        ar & averageSatisfaction;
    }
public:
    DriverSatisfaction();
    void updateSatisfaction(int satisfaction);
    int getNumOfTrips();
    int getSatisfaction();
};


#endif //EX2AP_DRIVERSATISFACTION_H
