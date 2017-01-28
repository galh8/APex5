//
// Created by amir on 26/11/16.
//

#include "Grid.h"

/**
 * Construct a Grid -vector of vectors (of GridNodes),
 * each gridNode represent a point on the grid.
 * @param rowsVal - number of rows of the grid.
 * @param columnsVal - number of columns of the grid.
 * @return - a new Grid with rowVal rows and columnsVal columns.
 */
Grid::Grid(int rowsVal, int columnsVal){
    Grid::rows = rowsVal;
    Grid::columns = columnsVal;
    Grid::gridMatrix.resize((unsigned long)Grid::columns+1);
    for(int i = 0; i<= Grid::columns ; i++) {
        gridMatrix[i].resize((unsigned long)Grid::rows+1);
        for(int j = 0; j<= Grid::rows; j++) {
            gridMatrix[i][j] = new GridNode(Point(i,j));
        }
    }
    setNeighbors();
}
/**
 * Desructor of Grid. release the memory allocated for all the gridNodes
 * inside the Grid.
 */
Grid::~Grid() {
    for(int i=0; i<= Grid::columns;i++) {
        for(int j=0; j<= Grid::rows; j++) {
            delete(gridMatrix[i][j]);
        }
    }
}
/**
 * The function adding neighbors to each GridNode,
 * Checking whether the neighbor exist, and if it is, adding it as
 * a neighbor of the gridNode.
 *
 */
void Grid::setNeighbors() {
    for(int i = 0; i<= Grid::columns; i++) {
        for(int j =0; j<=Grid::rows; j++) {
            //Set the left neighbor if it exist
            if(i-1>=0){
                gridMatrix[i][j]->setNeighbor(gridMatrix[i-1][j]);
            }
            //Set the upper neighbor if it exist
            if(j+1<=Grid::rows){
                gridMatrix[i][j]->setNeighbor(gridMatrix[i][j+1]);
            }
            //Set the right neighbor if it exist
            if(i+1<=Grid::columns){
                gridMatrix[i][j]->setNeighbor(gridMatrix[i+1][j]);
            }
            //Set the bottom neighbor if it exist
            if(j-1 >=0){
                gridMatrix[i][j]->setNeighbor(gridMatrix[i][j-1]);
            }

        }
    }
}
/**
 * The function returning a pointer to node (GridNode) , that its value
 * is point (the input of the function).
 * @param point - the required value of the Node to return.
 * @return - the GridNode that it's value is point.
 */
Node* Grid::getGridNode(Point point) {
    if( isOnGrid(point) ) {
        return gridMatrix[point.getX()][point.getY()];
    }
    return NULL;
}

int Grid::getRows() const {
    return rows;
}

int Grid::getColumns() const {
    return columns;
}

bool Grid::isOnGrid(Point point) {
    return (point.getX() <= columns) && (point.getX() >= 0) &&
                   (point.getY() <= rows) && (point.getY() >= 0) ? true : false;

}

void Grid::addObstacle(Point obsLocation) {
    Node* obstacleNode = getGridNode(obsLocation);
    obstacleNode->setReachable(false);

}
