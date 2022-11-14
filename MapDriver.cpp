//
// Created by xu zhang on 2022-09-24.
//

#include "MapLoader.h"
#include "MapDriver.h"
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

void testLoadMaps()
{
    cout << "Welcome to the RISK Game" << endl;
    cout << "Please choose your option to load the map: " << endl;

    cout << "1. Load default map: " << endl;
    cout << "2. Load maps" << endl;

    int option;

    cin >> option;

    while (!cin) {
        cout << "Please enter a number 1 or 2" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> option;
        while (option != 1 && option != 2)
        {
            cout << "Please enter a valid option: " << endl;
            cin >> option;
        }
    }



    string filePrefix = "../MapFiles/";

    if (option == 1)
    {
        MapLoader mapLoader;
        Map* map = mapLoader.LoadMap("C:/cpp/cpp_N23/MapFiles/3D.map");
        if (map->validate())
        {
            cout << "Map is valid" << endl;
            cout << "Map loaded successfully!" << endl;
        }
        else
        {
            cout << "Map is invalid" << endl;
            cout << "Map loaded failed!" << endl;
        }
    }/*
    else
    {
        // load all maps
        vector<Map*> maps;
        vector<string> mapFiles;
        for (const auto& entry : fs::directory_iterator(filePrefix))
        {
            // get all the filename in the directory
            mapFiles.push_back(entry.path());
        }

        // load all the maps
        for (auto & mapFile : mapFiles)
        {
            MapLoader mapLoader;
            Map* map = mapLoader.LoadMap(mapFile);


            if (map->validate())
            {
                cout << "Map " << mapFile << " is valid!" << endl;
                cout << "Map " << mapFile << " is Loaded!" << endl;
                maps.push_back(map);
            }
        }
    }*/
}