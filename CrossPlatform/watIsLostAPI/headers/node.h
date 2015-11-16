//
// Created by Alston on 11/14/2015.
//

#ifndef WATISLOST_NODE_H
#define WATISLOST_NODE_H

#include <string>
#include <vector>
#include "edge.h"

using namespace std;

class Edge;

class Node{
    private:
        int id, mapId, buildingId;
        bool searchable;
        string nodeName;
        double latitude, longitude, xPercent, yPercent;
        //Pathfinding stuff
        double totalDistance;
        bool visited;
        vector<Edge*> edges;
        Node *previous = NULL;
    public:
        Node(int id, int mapId, bool searchable, int buildingId, string nodeName,
             double latitude, double longitude, double xPercent, double yPercent);
        int getId();
        int getMapId();
        int getBuildingId();
        bool isSearchable();
        string getNodeName();
        double getLatitude();
        double getLongitude();
        double getXPercent();
        double getYPercent();

        //Pathfinding methods
        void connectNode(Node *other, double weight, bool outside);
        bool isVisited();
        void visit();
        double getTotalDistance();
        void setTotalDistance(double distance);
        vector<Edge*> getEdges();
        Node *getPrevious();
        void setPrevious(Node *previous);
        void reset();
};
#endif //WATISLOST_NODE_H
