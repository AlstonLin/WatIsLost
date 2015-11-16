/**
* This is the back end of WatIsLost, and is designed to be cross platform for
* Android, iOS, and Web. This will process all the json parsing, convert to graph,
* and pathfinding. The only functions that should be called here is void loadGraph(string json),
* double findPath[][](int nodeFromId, int nodToId) and string getNodeInfo[][]().
*/
#include <queue>
#include <iostream>
#include "rapidjson/document.h"
#include "headers/graph.h"

using namespace std;
using namespace rapidjson;

//Helper Methods
string intToString(int i){
	ostringstream oss;
	oss << i;
	return oss.str();
}

string doubleToString(double d){
	ostringstream oss;
	oss << d;
	return oss.str();
}

/**
 * This is the Singleton method; the point of access of the algorithm. There will only be a
 * single instance of Graph at all times, which can be accessed through this method.
 *
 * @return A pointer to the singleton Graph
 */

Graph::Graph(){}; //Makes the Graph constructor inaccessable outside of the class

Graph *Graph::instance = 0;

/**
* Loads the given json file to the graph that will be used
* for pathfinding. Shold be called before any other function is.
*
* @params json The json file, represented as a string, containing the graph info
*/
void Graph::loadGraph(string json){
    //int i = 0;
	Document doc;
	doc.Parse(json.c_str());
    assert(doc.IsObject());
    //Validation
    assert(doc.HasMember("maps"));
    assert(doc.HasMember("nodes"));
    assert(doc.HasMember("edges"));
    assert(doc.HasMember("buildings"));

	const Value& maps = doc["maps"];
	const Value& nodes = doc["nodes"];
	const Value& edges = doc["edges"];
	const Value& buildings = doc["buildings"];


	//Validation
	assert(maps.IsArray());
	assert(nodes.IsArray());
	assert(edges.IsArray());
	assert(buildings.IsArray());


	for (SizeType i = 0; i < maps.Size(); i++){
		const Value& map1 = maps[i];
		const Value& topLeftLoc = map1["topLeftLoc"];
		const Value& bottomRightLoc = map1["bottomRightLoc"];
		Map *mapObj = new Map(map1["id"].GetInt(), map1["name"].GetString(), map1["buildingId"].GetInt(),
						   topLeftLoc["latitude"].GetDouble(), topLeftLoc["longitude"].GetDouble(),
						   bottomRightLoc["latitude"].GetDouble(), bottomRightLoc["longitude"].GetDouble(),
						   map1["image"].GetString());
        int index = mapObj->getId();
        mapHash[index] = mapObj;
	}
	for (SizeType i = 0; i < nodes.Size(); i++){
		const Value& node = nodes[i];
		const Value& loc = node["location"];
		Node *nodeObj = new Node(node["id"].GetInt(), node["mapId"].GetInt(), node["searchable"].GetBool(),
								 node["buildingId"].GetInt(), node["name"].GetString(), loc["latitude"].GetDouble(),
								 loc["longitude"].GetDouble(), node["widthPercentage"].GetDouble(), node["heightPercentage"].GetDouble());
		nodeHash[nodeObj->getId ()] = nodeObj;
	}

	for (SizeType i = 0; i < edges.Size(); i++){
		const Value& edge = edges[i];
		int nodeAId = edge["nodeAId"].GetInt();
		int nodeBId = edge["nodeBId"].GetInt();
		double weight = edge["distance"].GetDouble();
		bool outside = edge["outside"].GetBool();

		nodeHash[nodeAId]->connectNode(nodeHash[nodeBId], weight, outside);
	}

	for (SizeType i = 0; i < buildings.Size(); i++){
		const Value& building = buildings[i];
		Building *buildingObj = new Building(building["id"].GetInt(), building["name"].GetString());
		buildingHash[buildingObj->getId()] = buildingObj;
	}
}

/**
* Uses Dijkstra's Algorithm to find a path between the two given
* node's id. Use getNodeInfo() to get the ids.
*
* @params nodeFromId The id of the starting node
* @params nodeToId The id of the ending node
* @return An Array of integers representing the IDs of the Nodes to travel to for the path
*/
vector<int> Graph::findPath(int nodeFromId, int nodeToId){
	vector<int> path = solveGraph(nodeHash[nodeFromId], nodeToId);
	return path;
}

/**
 * Use this to get information of all the Nodes on the graph.
 * @return An array of strings containing information of each node.
 * The first index is the node ID. The second index will have size
 * 3, with
 * [0] - node id,
 * [1] - map Id,
 * [2] - if the node should appear on the map (0 - false, 1 - true),
 * [3] - building name,
 * [4] - node name,
 * [5] - latitude of the location,
 * [6] - longitude of the location,
 * [7] - x location of the node on the map as a percentage of width,
 * [8] - y location as a percentage of height.
*/
vector< vector<string> > Graph::getNodeInfo(){
	map<int, Node*>::iterator iterator = nodeHash.begin();
	vector< vector<string> > info;
	while(iterator != nodeHash.end()){
		vector<string> nodeInfo(9);
		Node *node = iterator->second;

		nodeInfo[0] = intToString(node->getId());
		nodeInfo[1] = intToString(node->getMapId());
		nodeInfo[2] = intToString(node->isSearchable() ? 1 : 0);
		nodeInfo[3] = intToString(node->getBuildingId());
		nodeInfo[4] = node->getNodeName();
		nodeInfo[5] = doubleToString(node->getLatitude());
		nodeInfo[6] = doubleToString(node->getLongitude());
		nodeInfo[7] = doubleToString(node->getXPercent());
		nodeInfo[8] = doubleToString(node->getYPercent());

		info.push_back(nodeInfo);
		iterator++;
	}
	return info;
}

/**
 * Use this to get information of all the maps.
 * @return An array of strings containing information of each map.
 * The first index the information of each map. The second index contains
 * the individual pieces of information of each map. Indexes are
 * [0] - ID,
 * [1] - Name,
 * [2] - Building ID,
 * [3] - latitude of the top left corner,
 * [4] - longitude of the top left corner,
 * [5] - latitude of the bottom right corner,
 * [6] - longitude of the bottom right corner,
 * [7] - The filename of the image of the map
 */
vector< vector<string> > Graph::getMapInfo(){
	map<int, Map*>::iterator it = mapHash.begin();
	vector< vector<string> > info;
	while(it != mapHash.end()){
		vector<string> mapInfo(8);
		Map *map1 = it->second;

		mapInfo[0] = intToString(map1->getId());
		mapInfo[1] = map1->getName();
		mapInfo[2] = intToString(map1->getBuildingId());
		mapInfo[3] = doubleToString(map1->getTopLeftLat());
		mapInfo[4] = doubleToString(map1->getTopLeftLong());
		mapInfo[5] = doubleToString(map1->getBottomRightLat());
		mapInfo[6] = doubleToString(map1->getBottomRightLong());
		mapInfo[7] = map1->getImage();

		info.push_back(mapInfo);
        it++;
	}
	return info;
}

/**
 * Use this to get information of all the buildings.
 * @Return an array of building information (2d). The first index
 * is for each building. The second is the information, in the format
 * [0] - Index,
 * [1] - Name
 */
vector< vector<string> > Graph::getBuildingInfo(){
	map<int, Building*>::iterator it = buildingHash.begin();
	vector< vector<string> > info;
	while(it != buildingHash.end()){
		vector<string> buildingInfo(2);
		Building *building = it->second;
		buildingInfo[0] = intToString(it->first);
		buildingInfo[1] = building->getName();
		info.push_back(buildingInfo);
		it++;
	}
	return info;
}

//Dijkstra's Algorithm Here
struct Graph::Comparator{
	bool operator()(Node* lhs, Node* rhs) const{
		return lhs->getTotalDistance() > rhs->getTotalDistance();
	}
};
void Graph::resetGraph() {
	for (int i = 0; i < nodes.size(); i++){
		nodes[i].reset();
	}
}

vector<int> Graph::solveGraph(Node *start, int target) {
	//Setup
	vector<int> path;
	priority_queue<Node*, vector<Node*>, Comparator> queue;
	Node *current;
	resetGraph();
	//Add root
	queue.push(start);
	start->setTotalDistance(0);
	start->visit();
	//Relaxing Edges
	while (!queue.empty()){
		current = queue.top();
		queue.pop();
		vector<Edge*> edges = current->getEdges();
		for (int i = 0; i < edges.size(); i++){
			Edge *edge = edges[i];
			Node *neighbour = edge->getNodeTo();
			double distance = current->getTotalDistance() + edge->getWeight();
			if (distance < neighbour->getTotalDistance() || neighbour->getTotalDistance() == -1) {
				neighbour->setTotalDistance(distance);
				neighbour->setPrevious(current);
				if (!neighbour->isVisited()){
					neighbour->visit();
					queue.push(neighbour);
				}
			}
		}
	}
	//Generate the path
	current = nodeHash[target];
	while (current){
		path.insert(path.begin(),current->getId());
		current = current->getPrevious();
	}
	return path;
}

