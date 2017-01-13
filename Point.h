//
// Created by amir on 26/11/16.
//

#ifndef EX1TASK3_POINT_H
#define EX1TASK3_POINT_H
#include <iostream>
#include <boost/serialization/base_object.hpp>

#include <boost/archive/tmpdir.hpp>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>
using namespace std;

/**
 * Point class. Each Point containing a x and y coordinates. The class also
 * allowing to print a point by the format '(x,y)'.
 */
class Point {
private:
    int x;
    int y;
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & x;
        ar & y;
    }
public:
    Point(int xVal, int yVal);
    int getX() const;
    int getY() const;
    friend ostream&operator << (ostream& os, const Point &point);
    const Point operator+(const Point& point)const;
    bool operator==(const Point& point)const;
    bool operator!=(const Point& point)const;
};


#endif //EX1TASK3_POINT_H
