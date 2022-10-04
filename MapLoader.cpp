//
// Created by xu zhang on 2022-09-24.
//

#include "MapLoader.h"
#include "Continent.h"
#include "Territory.h"
#include "Map.h"
#include "GraphNode.h"
#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

Graph MapLoader::LoadMap() {

    Graph *graph = new Graph();

    ifstream input("001_I72_Ghtroc720.map");

    vector<Continent>* continents = new vector<Continent>();
    vector<Territory>* territories = new vector<Territory>();

    bool readingContinent = false;
    bool readingTerritory = false;

    if (!input.is_open()) {
        cout << "File not found!" << endl;
        return *graph;
    }

    while (!input.eof()) {
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
        if (readingContinent) {
        }
        if (readingTerritory) {
            vector<string> territoryInfo;

            stringstream ss(line);

            while (ss.good()) {
                string substr;
                getline(ss, substr, ',');
                territoryInfo.push_back(substr);
            }

            Territory* territory = new Territory();
            territory->setTerritoryName(new string(territoryInfo[0]));
            territory->setTerritoryX(new int(stoi(territoryInfo[1])));
            territory->setTerritoryY(new int(stoi(territoryInfo[2])));
            territory->setContinent(new string(territoryInfo[3]));
            territory->setTerritoryOwner(new string(""));
            territory->setTerritoryArmies(new int(0));

            vector<string>* territoryNeighbors = new vector<string>();

            for (int i = 4; i < territoryInfo.size(); i++) {
                territoryNeighbors->push_back(territoryInfo[i]);
            }

            territory->setTerritoryNeighbors(territoryNeighbors);

            GraphNode* graphNode = new GraphNode();
            graphNode->setVertex(territory);
            graphNode->setEdges(territoryNeighbors);

            graph->addGraphNode(graphNode);
            cout << "Territory: " << line << endl;
        }
    }


    input.close();

    return *graph;

}
