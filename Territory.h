//
// Created by xu zhang on 2022-09-24.
//

#ifndef CPP_N23_TERRITORY_H
#define CPP_N23_TERRITORY_H

#include <string>
#include <vector>

using namespace std;

class Territory {
private:
    string* territoryName;
    int* territoryX;
    int* territoryY;
    int* territoryArmies;
    string* continent;
    string* territoryOwner;
    vector<string>* territoryNeighbors;

public:
    Territory();
    Territory(string* territoryName, int* territoryX, int* territoryY, int* territoryArmies, string* continent, string* territoryOwner, vector<string>* territoryNeighbors);
    ~Territory();

    string* getTerritoryName();
    int* getTerritoryX();
    int* getTerritoryY();
    int* getTerritoryArmies();
    string* getContinent();
    string* getTerritoryOwner();
    vector<string>* getTerritoryNeighbors();

    void setTerritoryName(string* territoryName);
    void setTerritoryX(int* territoryX);
    void setTerritoryY(int* territoryY);
    void setTerritoryArmies(int* territoryArmies);
    void setContinent(string* continent);
    void setTerritoryOwner(string* territoryOwner);
    void setTerritoryNeighbors(vector<string>* territoryNeighbors);
};


#endif //CPP_N23_TERRITORY_H
