//
// Created by Alston on 11/14/2015.
//

#ifndef WATISLOST_MAP_H
#define WATISLOST_MAP_H

#include <string>
using namespace std;

class Map{
    private:
        int id, buildingId;
        string name, image;
        double topLeftLat, topLeftLong, bottomRightLat, bottomRightLong;

    public:
        Map(int id, string name, int buildingId, double topLeftLat, double topLeftLong, double bottomRightLat, double BottomRightLong, string image);
        int getId();
        int getBuildingId();
        string getName();
        double getTopLeftLat();
        double getTopLeftLong();
        double getBottomRightLat();
        double getBottomRightLong();
        string getImage();
};

#endif //WATISLOST_MAP_H
