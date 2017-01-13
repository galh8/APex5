//
// Created by amir on 27/11/16.
//

#ifndef EX1TASK3_BFS_H
#define EX1TASK3_BFS_H

#include "Node.h"
#include "Grid.h"
#include <stack>
#include <queue>
#include <iostream>
#include <vector>
/**
 * BFS Class implementing the bfs algorithm for finding the
 * shortest path between 2 nodes of a grid. The class containing just 1 static
 * method that calculating the shortest path between the nodes.
 */
class BFS {

public:
    /**
     * The function scanning the Map from start node to the destination node by
     * BFS and finding the shortest route between the 2 nodes/
     * @param startNode - The node to start the scan from.
     * @param destNode - The destination node, to find the shortest route to.
     */
    static vector<Node*> BFS_Navigate(Node* startNode,Node* destNode);


};


#endif //EX1TASK3_BFS_H
