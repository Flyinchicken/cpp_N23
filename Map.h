//
// Created by xu zhang on 2022-09-24.
//

#ifndef CPP_N23_MAP_H
#define CPP_N23_MAP_H

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

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


};

class Graph
{
private:
    unordered_map<string,Territory*> nodes;
    unordered_map<string,vector<string>> edges;

public:
    // setters and getters:
    void addNode(std::string);
    void addNeighbor(std::string territory, std::string neighbor);

    Territory* getNode(std::string);
    std::vector<std::string>* getNeighbours(std::string);

    // map methods:
    bool validate();

};

class Continent : public Graph
{
private:
    string continentName;
    int bonusArmy;

public:
    // contructors and destructor
    Continent();
    Continent(string continentName, int bonusArmy);
    ~Continent();

    // getter

    string getContinentName() const;
    int getBonusArmy() const;

    // setter

    void setContinentName(string continentName);
    void setBonusArmy(int bonusArmy);

};



class Map : public Graph
{
private:
    unordered_map<string, Continent*> continents;

public:
    // constructors and destructors
    Map();

};
#endif //CPP_N23_MAP_H
