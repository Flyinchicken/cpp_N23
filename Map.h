//
// Created by xu zhang on 2022-09-24.
// Added Map, Continent, Graph methods for validation by Weijie Tan on 2022-10-08
//

#ifndef CPP_N23_MAP_H
#define CPP_N23_MAP_H

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <set>
#include <stack>

using namespace std;

class Territory
{
private:
    string name;
    string continent;
    int armies;
    string owner;
    bool occupied;

public:
    // constructor and destructor
    Territory();

    Territory(string name, string continent, int armies, string owner);

    // copy constructor?

    // getter
    string getName() const;

    string getContinent() const;

    int getArmy() const;

    string getOwner() const;

    bool isOccupied() const;

    // setter

    void setName(string name);

    void setContinent(string continent);

    void setArmy(int army);

    void setOwner(string owner);

    void setOccupied(bool occupied);

    // operator overload
    // +, <<, =
    void operator+();

    string operator<<(Territory*);

    void operator=(Territory*);
};

class Graph
{
public:
    unordered_map<string, Territory*> nodes;
    unordered_map<string, vector<string>> edges;

    // setters and getters:
    void addNode(std::string);
    void addNeighbor(std::string territory, std::string neighbor);

    Territory* getNode(std::string);
    std::vector<std::string>* getNeighbours(std::string);

    // map methods:
    bool validate();
    bool isConnected();

};

class Continent : public Graph
{
private:
    string continentName;
    int bonusArmy;
    // Player* owner;

public:
    // contructors and destructor
    Continent();
    Continent(string continentName, int bonusArmy);
    ~Continent();

    // getter

    string getContinentName() const;
    int getBonusArmy() const;
    string getOwner();

    // setter

    void setContinentName(string continentName);
    void setBonusArmy(int bonusArmy);

    // operator overload
    // +, <<, =
    void operator+();

    string operator<<(Continent*);

    void operator=(Continent*);
};



class Map : public Graph
{
private:
    unordered_map<string, Continent*> continents;

public:
    // constructors and destructors
    Map();
    ~Map();

    // Map methods:
    void addContinent(string Continent_Name, int bonus);


    bool continentsAllSubgraphs();
    bool validate();
    bool territoryInUniqueContinent();

    // operator overload
    // +, <<, =
    void operator+();

    string operator<<(Map*);

    void operator=(Map*);

};
#endif //CPP_N23_MAP_H
