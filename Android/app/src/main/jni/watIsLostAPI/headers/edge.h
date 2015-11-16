#ifndef WATISLOST_EDGE_H
#define WATISLOST_EDGE_H

#include "node.h"

class Node;

class Edge{
    private:
        Node *nodeTo = NULL;
        double weight;
        bool outside;
    public:
        Edge(Node *nodeFrom, double weight, bool outside);
        Node *getNodeTo();
        double getWeight();
        bool isOutside();
};

#endif //WATISLOST_EDGE_H
