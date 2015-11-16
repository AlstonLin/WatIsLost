#include "headers/building.h"

Building::Building(int id, string name){
    this->id = id;
    this->name = name;
}

int Building::getId(){
    return id;
}
string Building::getName(){
    return name;
}
