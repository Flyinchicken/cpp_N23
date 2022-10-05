//
// Created by xu zhang on 2022-09-24.
//

#include "MapLoader.h"
#include "Map.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <filesystem>

namespace fs = std::filesystem;

using namespace std;

void MapLoader::LoadMap() {

//    cout << "Welcome to RISK game!" << endl;
//    cout << "Please enter the map file name: " << endl;
//    string fileName;
//    cin >> fileName;

    cout << "Loading map..." << endl;

    vector<string> mapFiles;

    string path = "../MapFiles";
    for (const auto & entry : fs::directory_iterator(path)){
        mapFiles.push_back(entry.path());
    }
//        cout << entry.path() << endl;

    for (int i = 0; i < mapFiles.size(); i++) {
        cout << mapFiles[i].replace(0,12, "") << endl;
    }

//    cout << "Please enter the map file name: " << endl;

    ifstream input("../MapFiles/3D.map");

    if(!input.is_open()) {
        cout << "File not found!" << endl;
        return;
    }

    vector<Continent>* continents = new vector<Continent>();
    vector<Territory>* territories = new vector<Territory>();

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
            Continent continent = Continent();
            continent.name = line.substr(0, line.find('='));
            continent.value = stoi(line.substr(line.find('=') + 1));
            continents->push_back(continent);
        }

        if(readingTerritory) {
            vector<string> territoryInfo;

            stringstream ss(line);

            while (ss.good()) {
                string substr;
                getline(ss, substr, ',');
                territoryInfo.push_back(substr);
            }
        }
    }

//    ifstream input("001_I72_Ghtroc720.map");
//

//
//
//
//
//
//    bool readingContinent = false;
//    bool readingTerritory = false;
//
//    if (!input.is_open()) {
//        cout << "File not found!" << endl;
//        return *graph;
//    }
//
//    while (!input.eof()) {
//        string line;
//        getline(input, line);
//        if (line == "[Continents]\r") {
//            readingContinent = true;
//            continue;
//        }
//        if (line == "[Territories]\r") {
//            readingContinent = false;
//            readingTerritory = true;
//            continue;
//        }
//        if (readingContinent) {
//        }
//        if (readingTerritory) {
//            vector<string> territoryInfo;
//
//            stringstream ss(line);
//
//            while (ss.good()) {
//                string substr;
//                getline(ss, substr, ',');
//                territoryInfo.push_back(substr);
//            }
//
//
//        }
//    }
//
//
    input.close();

}
