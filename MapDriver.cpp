//
// Created by xu zhang on 2022-09-24.
//

#include "MapLoader.h"
#include "MapDriver.h"
#include <iostream>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;

void MapDriver::run() {
    cout << "Welcome to the RISK Game" << endl;
    cout << "Please choose your option to load the map: " << endl;

    cout << "1. Load default map: " << endl;
    cout << "2. Load maps" << endl;

    int option;

    cin >> option;

    while (option != 1 && option != 2) {
        cout << "Please enter a valid option: " << endl;
        cin >> option;
    }

    string filePrefix = "../MapFiles/";

    if (option == 1) {
        MapLoader mapLoader;
        Map* map = mapLoader.LoadMap("3D.map");
        cout << "Map loaded successfully!" << endl;
    } else {
        vector<Map*> maps;
        vector<string> mapFiles;
        for (const auto & entry : fs::directory_iterator(filePrefix)){
            mapFiles.push_back(entry.path());
        }

        for (int i = 0; i < mapFiles.size(); i++) {
            MapLoader mapLoader;
            Map* map = mapLoader.LoadMap(mapFiles[i]);


            if (map->validate()) {
                cout << "Map " << mapFiles[i] << " is valid!" << endl;
                cout << "Map " << mapFiles[i] << " is Loaded!" << endl;
                maps.push_back(map);
            }
        }
    }
}
