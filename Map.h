//
// Created by xu zhang on 2022-09-24.
//

#ifndef CPP_N23_MAP_H
#define CPP_N23_MAP_H

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <set>
#include <stack>
#include "Player.h"

using namespace std;
class Player;

class Territory
{
private:
    string* territoryName;
    string* continentName;
    int armyNumber;
    bool isOccupied;
    Player* owner;

public:
    // constructor and destructor
    Territory();

    Territory(string* territoryName, string* continentName, int armyNumber, bool isOccupied, Player* owner);

    ~Territory();

    // Deep copy constructor
    Territory(const Territory& territory);

    // Deep copy assignment operator
    Territory& operator=(const Territory& territory);

    // iostream operator
    friend ostream& operator<<(ostream& outs, Territory& theObject);

    // getter and setter
    string* getTerritoryName() const;

    void setTerritoryName(string* territoryName);

    string* getContinentName() const;

    void setContinentName(string* continentName);

    int getArmyNumber() const;

    void setArmyNumber(int armyNumber);

    bool getOccupied() const;

    void setOccupied(bool isOccupied);

    Player* getOwner() const;

    void setOwner(Player* owner);

    // other methods

    // add army to the territory
    void addArmy(int armyNumber);

    // remove army from the territory
    void removeArmy(int armyNumber);

};

class Graph
{
public:
    unordered_map<string, Territory*> nodes;
    unordered_map<string, vector<string>> edges;

    // setters and getters:
    void addNode(std::string);
    void addNode(string,Territory*);
    void addNeighbor(std::string territory, std::string neighbor);
    void addNeighbor(string territory, vector<string> neighbor);

    Territory* getNode(std::string);
    std::vector<std::string> getNeighbours(std::string);

    virtual
    // map methods:
//    bool validate();
    bool isConnected();

};

class Continent : public Graph
{
private:
    string* continentName;
    int bonusArmy;
    //Player* owner;

public:
    // contructors and destructor
    Continent();
    Continent(string* continentName, int bonusArmy);
    ~Continent();

    // Deep copy constructor
    Continent(const Continent& continent);

    // Deep copy assignment operator
    Continent& operator=(const Continent& continent);

    // iostream operator
    friend ostream& operator<<(ostream& outs, Continent& theObject);

    // getter

    string* getContinentName() const;
    int getBonusArmy() const;

    // setter

    void setContinentName(string* continentName);
    void setBonusArmy(int bonusArmy);

};


class Map : public Graph
{

public:
    unordered_map<string, Continent*> continents;

public:
// constructors and destructors
Map();
~Map();
Map(const Map& map);


// Map methods:
void addContinent(string Continent_Name, int bonus);
bool continentsAllSubgraphs();
bool validate();
bool territoryInUniqueContinent();

// operator overload
// +, <<, =
void operator+();
friend ostream& operator<<(ostream& os, Map& map);
void operator=(Map*);

};
#endif //CPP_N23_MAP_H
