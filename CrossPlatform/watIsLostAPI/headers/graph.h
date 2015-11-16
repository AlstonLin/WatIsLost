#ifndef WATISLOST_GRAPH_H
#define WATISLOST_GRAPH_H

#include <vector>
#include <string>
#include "building.h"
#include "node.h"
#include "edge.h"
#include "map.h"
#include <map>
#include <sstream>

class Graph { //Hide these functions
    private:
        static Graph *instance;
        struct Comparator;
        vector<Node> nodes;
        map<int, Node*> nodeHash;
        map<int, Map*> mapHash;
        map<int, Building*> buildingHash;
        vector<int> solveGraph(Node *start, int target);
        Graph();
        void resetGraph();


    public:
        static Graph* getInstance(){
            if (instance == NULL) instance = new Graph();
            return instance;
        }
        void loadGraph(string json);
        vector<int> findPath(int nodeFromId, int nodeToId);
        vector< vector<string> > getNodeInfo();
        vector< vector<string> > getMapInfo();
        vector< vector<string> > getBuildingInfo();
};
#endif //WATISLOST_GRAPH_H
