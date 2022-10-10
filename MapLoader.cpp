//
// Created by xu zhang on 2022-09-24.
//
#include "Map.h"
#include "MapLoader.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <filesystem>


namespace fs = std::filesystem;

using namespace std;

Map* MapLoader::LoadMap(string fileName) {

    cout << "Loading map..." << endl;

    ifstream input(fileName);

    if(!input.is_open()) {
        cout << "File not found!" << endl;
        return nullptr;
    }

    Map* map = new Map();

    bool readingContinent = false;
    bool readingTerritory = false;

    while( !input.eof() ) {
        string line;
        getline(input, line);
        if (line == "[Continents]\r") {
            readingContinent = true;
            continue;
        }
        if (line == "[Territories]\r") {
            readingContinent = false;
            readingTerritory = true;
            continue;
        }

        if(readingContinent) {

            if (line != "\r") {
                map->addContinent(line.substr(0, line.find("=")), stoi(line.substr(line.find("=") + 1)));
            }

        }

        if(readingTerritory) {
            vector<string> territoryInfo;

            stringstream ss(line);

            while (ss.good()) {
                string substr;
                getline(ss, substr, ',');
                territoryInfo.push_back(substr);
            }

            if (territoryInfo.size() > 1) {
                map->addNode(territoryInfo[0]);
                map->continents.at(territoryInfo[3])->addNode(territoryInfo[0],map->nodes.at(territoryInfo[0]));
            }

            for (int i = 4; i < territoryInfo.size(); i++) {
                map->addNeighbor(territoryInfo[0], territoryInfo[i]);
                map->continents.at(territoryInfo[3])->addNeighbor(territoryInfo[0],map->edges.at(territoryInfo[0]));
            }

        }
    }

    input.close();

    return map;

}
