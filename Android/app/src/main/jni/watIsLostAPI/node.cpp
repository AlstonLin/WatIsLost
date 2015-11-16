#include "headers/node.h"
using namespace std;

Node::Node(int id, int mapId, bool searchable, int buildingId, string nodeName, double latitude, double longitude, double xPercent, double yPercent){
    this->id = id;
    this->mapId = mapId;
    this->searchable = searchable;
    this->buildingId = buildingId;
    this->nodeName = nodeName;
    this->latitude = latitude;
    this->longitude = longitude;
    this->xPercent = xPercent;
    this->yPercent = yPercent;
    //Pathfinding
    this->totalDistance = -1;
    this->edges = vector<Edge*> ();
    this->visited = false;
}

int Node::getId(){
    return id;
}

int Node::getMapId(){
    return mapId;
}

int Node::getBuildingId() {
    return buildingId;
}

bool Node::isSearchable() {
    return searchable;
}

string Node::getNodeName() {
    return nodeName;
}

double Node::getLatitude(){
    return latitude;
}

double Node::getLongitude(){
    return longitude;
}

double Node::getXPercent(){
    return xPercent;
}

double Node::getYPercent(){
    return yPercent;
}


//PATH FINDING
bool Node::isVisited() {
    return visited;
}

void Node::visit() {
    this->visited = true;
}

void Node::setPrevious(Node *previous) {
    this->previous = previous;
}

double Node::getTotalDistance() {
    return totalDistance;
}

void Node::setTotalDistance(double totalDistance){
    this->totalDistance = totalDistance;
}

vector<Edge*> Node::getEdges(){
    return edges;
}

Node *Node::getPrevious() {
    return previous;
}

void Node::reset(){
    previous = NULL;
    visited = false;
    totalDistance = -1;
}

void Node::connectNode(Node *other, double weight, bool outside){
    Edge *edge1 = new Edge(other, weight, outside);
    Edge *edge2 = new Edge(this, weight, outside);
    this->edges.push_back(edge1);
    other->edges.push_back(edge2);
}
