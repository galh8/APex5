//
// Created by amir on 26/11/16.
//

#include "Point.h"


Point::Point(int xVal,int yVal) {
    Point::x = xVal;
    Point::y = yVal;
}
/**
 * Getter for the x coordinate.
 * @return - the x coordinate of the point.
 */
int Point::getX() const{
    return x;
}
/**
 * Getter for the y coordinate.
 * @return the y coordinate of the point.
 */
int Point::getY() const{
    return y;
}
/**
 * Overloading the << operator for printing the object in the required format - '(x,y)'.
 */
ostream& operator << (ostream& os,const Point &point) {
    return os<<'('<<point.getX()<<','<<point.getY()<<')';
}

/**
 * Overloading the + operator.
 */
const Point Point::operator+(const Point& point)const{
    return Point(x+point.getX(),y + point.getY());
}

/**
 * Overloading the == operator.
 */
bool Point::operator==(const Point &point) const {
    return x==point.getX() && y==point.getY();
}

/**
 * Overloading the != operator.
 */
bool Point::operator!=(const Point &point) const {
    return !(*this==point);
}