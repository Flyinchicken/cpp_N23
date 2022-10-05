#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>


class Map : public Graph
{
    private:
    std::unordered_map<std::string, Continent*>* continents;

    public:
    // constructors and destructors
    Map();

};

class Graph
{
    private:
    std::unordered_map<std::string,Territory*>* nodes;
    std::unordered_map<std::string,std::vector<std::string>*>* edges;

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
    std::string* continentName;

    public:
    // contructors and destructor
    Continent();
    ~Continent();

};

class Territory 
{
    private:
    std::string* countryName;
    int* numberOfArmies;
    // Player* owner;
    bool* owned;

    public:
    // constructor and destructor
    Territory();

    Territory(std::string);
    
    // 
    bool isOwned();


};

class MapLoader
{
    public:
    Map* loadMap();

};

#endif 