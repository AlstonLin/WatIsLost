#include "headers/edge.h"

Edge::Edge(Node *nodeTo, double weight, bool outside){
    this->nodeTo = nodeTo;
    this->weight = weight;
    this->outside = outside;
}

Node *Edge::getNodeTo() {
    return nodeTo;
}

double Edge::getWeight() {
    return weight;
}

bool Edge::isOutside(){
    return outside;
}