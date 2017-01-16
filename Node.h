//
// Created by amir on 26/11/16.
//
#include "Point.h"
#include <vector>

using namespace std;



#ifndef EX1TASK3_NODE_H
#define EX1TASK3_NODE_H
#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
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
/**
 * An abstract class representing a node of data structure, allowing to
 * perform some activities on it. The activities make it possible to search inside the data structure.
 */
class Node  {
protected:
    bool visited;
    bool reachable;
    Node *parent;
    vector<Node*> neightboors;
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & visited;
//        ar & reachable;
//        ar & parent;
//        ar & neightboors;
    }
public:
    virtual bool beenVisited() = 0;
    virtual Node* getParent() = 0;
    virtual vector<Node *> getNeightboors() =0;
    virtual void setNeighbor(Node* neighbor) = 0;
    virtual void setVisitedFlag(bool visited) = 0;
    virtual void setParent(Node* parent)=0;
    virtual std::string valueString()  = 0;
    friend ostream&operator << (ostream& os,  Node &n);
    virtual void* getValue() = 0;
    virtual bool isReachable() = 0;
    virtual void setReachable(bool reachFlag) = 0;


};


#endif //EX1TASK3_NODE_H
