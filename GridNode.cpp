//
// Created by amir on 26/11/16.
//

#include "GridNode.h"

using namespace std;

/**
 * Construct a GridNode with point type value.
 * @param value - the value of the gridNode(Point type)
 * @return  - new GridNode with 'value' value.
 */
GridNode::GridNode(Point value) : value(value){
    visited = false;
    reachable = true ; //the node is reachable by default.
}

GridNode::GridNode() : value(value) {

}

/**
 * Checking whether the gridNode marked as visited.
 * @return - true - if the gridNode visited and false it isn't.
 */
bool GridNode::beenVisited(){
    return visited;
}

/**
 * The function creating  a new string representing the value of
 * the grid node. The format is '(x,y)' .
 * @return - String representing the value of the grid node.
 */
std::string GridNode::valueString()  {
    std::ostringstream oss;
    oss<< "("<< value.getX()<<","<<value.getY()<<")";
    return oss.str();

}

/**
 *
 * Overload the << operator for printing a Node Value by the required format '(x,y)'.
 */
ostream& operator << (ostream& os, Node& n) {
     os<<n.valueString();
    return os;
}

/**
 * Getter for parent node pointer.
 * @return Pointer to the parent node of the current grid Node.
 */
Node* GridNode::getParent() {
    return parent;
}

/**
 * getter for neighbors vector.
 * @return  a vector containing all the neightbors of the node. (the order is 9,12,3,6).
 */
vector<Node*> GridNode::getNeightboors() {
    return neightboors;
}

/**
 * Changing the 'visited' flag of the gridNode.
 * @param visited - the boolen value to set as visited flag.
 */
void GridNode::setVisitedFlag(bool visited) {
    GridNode::visited = visited;
}
/**
 *  Setting the parent of the gridNode.
 * @param parent  - the Node* to set as parent.
 */
void GridNode::setParent(Node* parent) {
    GridNode::parent = parent;
}

/**
 * Adding a neighbor to the end of the neighbors vector of the gridNode.
 * @param neighbor - the node* to add as a neighbor of the gridNode.
 */
void GridNode::setNeighbor(Node *neighbor) {
    GridNode::neightboors.push_back(neighbor);
}

/**
 *
 * @return the value of the GrindNode.
 */
void *GridNode::getValue() {
    return &value;
}

/**
 * @return if the GrindNode is reachable.
 */
bool GridNode::isReachable() {
    return reachable;
}

/**
 * set if the node is reachable.
 * @param reachFlag - if the GrindNode is reachable.
 */
void GridNode::setReachable(bool reachFlag) {
    reachable = reachFlag ;
}


