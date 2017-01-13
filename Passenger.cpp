//
// Created by amir on 01/12/16.
//

#include "Passenger.h"

Passenger::Passenger(Node *source, Node *dest) {
    sourcePoint = source;
    destinationPoint = dest;
}

Node* Passenger::getDestinationPoint() {
    return NULL;
}
Node* Passenger::getSourcePoint() {
    return NULL;
}

void Passenger::setSourcePoint(Node *source) {

}

void Passenger::setDestinationPoint(Node *dest) {

}

int Passenger::getPassengerSatisfaction() {
    return 0;
}

