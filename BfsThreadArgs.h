//
// Created by amir on 14/01/17.
//

#ifndef PLAYWITHSOCKETS_BFSTHREADARGS_H
#define PLAYWITHSOCKETS_BFSTHREADARGS_H


#include "Node.h"
#include <vector>

class BfsThreadArgs {
private:
    Node *start;
    Node *dest;
    vector<Node*> *tripRoute;
    bool *isCalculated;
public:
    BfsThreadArgs(Node *start,Node *dest,vector<Node*> *tripRoute,bool *routeCalc);
    Node* getStart();
    Node* getDest();
    vector<Node*> *getTripRoute();
    void setTripRoute(vector<Node* > &route);
    void setRouteCalculated();

};


#endif //PLAYWITHSOCKETS_BFSTHREADARGS_H
