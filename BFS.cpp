//
// Created by amir on 27/11/16.
//

#include "BFS.h"

using namespace std;


vector<Node*> BFS::BFS_Navigate(Node *startNode, Node *destNode) {
    //vector that saves the node we've changed. to change it back when finish.
    vector<Node*>backupChangedNodes;    vector<Node*> route ;
    //if one of the locations is null, there is no route.
    if((startNode == NULL)||(destNode== NULL)){
        return route;
    }
    //Change the flag of the node to 'visited'.
    startNode->setVisitedFlag(true);
    backupChangedNodes.push_back(startNode);
    //The queue of nodes for implementing the algorithm by.
    queue <Node*> queueNavigator;
    //Stack for printing the route at the end in a proper way.
    stack<Node*> printingStack;
    queueNavigator.push(startNode);
    startNode->setParent(NULL);
    //While the scan isn't finished.
    while(!queueNavigator.empty()) {
        //Current node points to the next node (the first node of the queue).
        Node *currentNode = queueNavigator.front();
        queueNavigator.pop();
        //The destination node founded, so we should print the route.
        if(currentNode == destNode) {
            while(currentNode!=NULL) {
                //Pushing the stack all the nodes from current node to his parents.
                printingStack.push(currentNode);
                //cout<< "BLA "<< *(Point*)(currentNode->getValue())<<" ";
                currentNode = currentNode->getParent();
            }
            break;
        }
        /*for each neighbor of current node, if its havent visited yet, change his parent
        *to current node, insert it to the queue, and change it's flag to 'visited'.*/
        for(int i=0; i <currentNode->getNeightboors().size();i++){
            Node* tempNode = currentNode->getNeightboors()[i];
            if( (!tempNode->beenVisited())&&(tempNode->isReachable())) {
                backupChangedNodes.push_back(tempNode);
                tempNode->setParent(currentNode);
                queueNavigator.push(tempNode);
                tempNode->setVisitedFlag(true);
            }
        }
    }
    while (!printingStack.empty()) {
        //Printing the stack.
        //cout<<printingStack.top()->valueString()<<endl;
        route.push_back(printingStack.top());
        printingStack.pop();
    }
    //resetting the nodes visited flag and parents.
    for(int i=0;i<backupChangedNodes.size();i++){
        backupChangedNodes[i]->setVisitedFlag(false);
        backupChangedNodes[i]->setParent(NULL);
    }

    return route;
}