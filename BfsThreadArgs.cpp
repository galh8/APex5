//
// Created by amir on 14/01/17.
//

#include "BfsThreadArgs.h"

BfsThreadArgs::BfsThreadArgs(Node *start,Node *dest,vector<Node*> *tripRoute,bool *routeCalc):
    start(start) , dest(dest), tripRoute(tripRoute),isCalculated(routeCalc){}

void BfsThreadArgs::setTripRoute(vector<Node* > &route) {
    *tripRoute = route;
}

void BfsThreadArgs::setRouteCalculated() {
    *isCalculated = true;
}

Node *BfsThreadArgs::getStart()  {
    return start;
}
Node *BfsThreadArgs::getDest()  {
    return dest;
}
vector<Node* >*BfsThreadArgs::getTripRoute() {
    return tripRoute;
}