//
// Created by xu zhang on 2022-09-24.
//

#ifndef CPP_N23_MAPLOADER_H
#define CPP_N23_MAPLOADER_H

#include "Map.h"

class MapLoader {
public:
    MapLoader() {};
    ~MapLoader() = default;

    Map* LoadMap(string filename);
};



#endif //CPP_N23_MAPLOADER_H