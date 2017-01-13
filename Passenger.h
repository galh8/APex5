//
// Created by amir on 01/12/16.
//

#ifndef EX2AP_PASSENGER_H
#define EX2AP_PASSENGER_H

#include "Node.h"

class Passenger {
private:
    Node* sourcePoint;
    Node* destinationPoint;
public:
    Passenger(Node* source,Node* dest);
    Node* getSourcePoint();
    Node* getDestinationPoint();
    void setSourcePoint(Node* source);
    void setDestinationPoint(Node* dest);
    int getPassengerSatisfaction();

};


#endif //EX2AP_PASSENGER_H
