#ifndef WATISLOST_BUILDING_H
#define WATISLOST_BUILDING_H
#include <string>
using namespace std;
class Building {
    private:
        int id;
        string name;
    public:
        Building(int id, string name);
        int getId();
        string getName();
};


#endif //WATISLOST_BUILDING_H
