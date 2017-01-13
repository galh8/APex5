//
// Created by amir on 26/11/16.
//

#ifndef EX1TASK3_GRID_H
#define EX1TASK3_GRID_H

#include "GridNode.h"
#include <vector>
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

/**
 * Grid Class, constructing a Grid of grid nodes (implementing by a a vector of
 * vectors (of GridNodes)). The Grid size is rows * columns. The class also
 * determine the neighbors of each gridNode it contains.
 */
class Grid {
private:
    vector<vector<GridNode*> > gridMatrix;
    int rows;
    int columns;
    void setNeighbors();

    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) {

        ar & gridMatrix;
        ar & rows;
        ar & columns;
    }

public:
    Grid(int rowsVal, int columnsVal);
    ~Grid();
    Node* getGridNode(Point point);
    int getRows() const;
    int getColumns() const;
    bool isOnGrid(Point point);
    void addObstacle(Point obsLocation);

};


#endif //EX1TASK3_GRID_H
