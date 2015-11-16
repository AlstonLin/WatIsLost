#include "headers/map.h"

Map::Map(int id, string name, int buildingId, double topLeftLat, double topLeftLong, double bottomRightLat, double BottomRightLong, string image){
    this->id = id;
    this->buildingId = buildingId;
    this->name = name;
    this->topLeftLat = topLeftLat;
    this->topLeftLong = topLeftLong;
    this->bottomRightLat = bottomRightLat;
    this->bottomRightLong = bottomRightLong;
    this->image = image;
}

int Map::getId(){
    return id;
}
int Map::getBuildingId(){
    return buildingId;
}
string Map::getName(){
    return name;
}
double Map::getTopLeftLat(){
    return topLeftLat;
}
double Map::getTopLeftLong(){
    return topLeftLong;
}
double Map::getBottomRightLat(){
    return bottomRightLat;
}
double Map::getBottomRightLong(){
    return bottomRightLong;
}
string Map::getImage() {
    return image;
}
