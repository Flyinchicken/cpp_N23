//
// Created by xu zhang on 2022-09-24.
// Implemented Map, Continent, Graph methods for validation by Weijie Tan on 2022-10-08
//

#include "Map.h"

Territory::Territory() {
    territoryName = nullptr;
    continentName = nullptr;
    armyNumber = 0;
    isOccupied = false;
    owner = nullptr;
}

Territory::Territory(string* territoryName, string* continentName, int armyNumber, bool isOccupied, Player* owner) {
    this->territoryName = territoryName;
    this->continentName = continentName;
    this->armyNumber = armyNumber;
    this->isOccupied = isOccupied;
    this->owner = owner;
}

Territory::~Territory() {
    delete territoryName;
    delete continentName;
    delete owner;
}

Territory::Territory(const Territory& territory) {
    territoryName = new string(*territory.territoryName);
    continentName = new string(*territory.continentName);
    armyNumber = territory.armyNumber;
    isOccupied = territory.isOccupied;
    // Here we need to deep copy the owner @Xin Jia
    //owner = new Player(*territory.owner);
    owner = new Player();

}

Territory& Territory::operator=(const Territory& territory) {
    if (this != &territory) {
        delete territoryName;
        delete continentName;
        delete owner;
        territoryName = new string(*territory.territoryName);
        continentName = new string(*territory.continentName);
        armyNumber = territory.armyNumber;
        isOccupied = territory.isOccupied;
        owner = new Player(*territory.owner);
    }
    return *this;
}

ostream& operator<<(ostream& outs, Territory& o) {
    outs << "Territory Name: " << *o.territoryName << endl;
    outs << "Continent Name: " << *o.continentName << endl;
    outs << "Army Number: " << o.armyNumber << endl;
    outs << "Is Occupied: " << o.isOccupied << endl;
    outs << "Owner: " << *o.owner << endl;
    return outs;
}

string* Territory::getTerritoryName() const {
    return territoryName;
}

void Territory::setTerritoryName(string* territoryName) {
    this->territoryName = territoryName;
}

string* Territory::getContinentName() const {
    return continentName;
}

void Territory::setContinentName(string* continentName) {
    this->continentName = continentName;
}

int Territory::getArmyNumber() const {
    return armyNumber;
}

void Territory::setArmyNumber(int armyNumber) {
    this->armyNumber = armyNumber;
}

bool Territory::getOccupied() const {
    return isOccupied;
}

void Territory::setOccupied(bool isOccupied) {
    this->isOccupied = isOccupied;
}

Player* Territory::getOwner() const {
    return owner;
}

void Territory::setOwner(Player* owner) {
    this->owner = owner;
}

void Territory::addArmy(int armyNumber) {
    this->armyNumber += armyNumber;
}

void Territory::removeArmy(int armyNumber) {
    if (this->armyNumber - armyNumber < 0) {
        this->armyNumber = 0;
    } else {
        this->armyNumber -= armyNumber;
    }
}
// End of the Territory Class *********************************************************************************************************

// Methods implementation of the Graph Class ******************************************************************************************
void Graph::addNode(string territory_name){
    if(this->nodes.count(territory_name) == 0){
        this->nodes.insert_or_assign(territory_name, new Territory());
    }

}

Territory* Graph::getNode(string territory_name){
    return nodes.at(territory_name);
}

vector<Territory*> Graph::getNodesPtr(){
    vector<Territory*> territoriesPtr;
    for(auto& kv : this->nodes){
        territoriesPtr.push_back(kv.second);
    }
    return territoriesPtr;
}

vector<Territory*> Graph::getNeighboursPtr(string territory_name){
    vector<Territory*> neighborsPtr;
    for(auto& name : edges.at(territory_name)){
        neighborsPtr.push_back(getNode(name));
    }
    return neighborsPtr;
}

void Graph::addNeighbor(string territory, string neighbor){
    this->edges[territory].push_back(neighbor);
}

void Graph::addNeighbor(string territory, vector<string> neighbor){
    this->edges[territory] = neighbor;
}

void Graph::addNode(string territory_name, Territory* Territory){
    if(this->nodes.count(territory_name) == 0){
        this->nodes.insert_or_assign(territory_name, Territory);
    }
}

bool Graph::isConnected() {
    // Check if the graph is strongly connected
    // Definition used here: every node can reach all the rest of the nodes in the map

    // kv pair: kv.first is the name of each territory
    for (auto& kv : this->nodes) {
        // reached is a set to keep track of all the nodes reachable starting from the current territory
        set<string> reached;

        // start of the depth first search of the graph to traverse every node
        stack<string> neighborStack;
        neighborStack.push(kv.first);
        while (!neighborStack.empty()) {
            string current = neighborStack.top();
            neighborStack.pop();
            reached.insert(current);
            for (auto& neighbor : this->edges.at(current)) {
                if (reached.count(neighbor) != 1) {
                    neighborStack.push(neighbor);
                }
            }
        }

        // since all nodes must be reachable, the sides of the reached set should be the same as the total number of Territories
        if (reached.size() != this->nodes.size()) {
            return false;
        }
    }
    return true;
}
// End of the Graph Class *************************************************************************************************************


Continent::Continent() {
    this->continentName = nullptr;
    this->bonusArmy = 0;
}

Continent::Continent(string* name, int bonus) {
    this->continentName = name;
    this->bonusArmy = bonus;
}

Continent::~Continent() {
    delete continentName;
}

string* Continent::getContinentName() const {
    return this->continentName;
}

int Continent::getBonusArmy() const {
    return this->bonusArmy;
}

void Continent::setContinentName(string* name) {
    this->continentName = name;
}

void Continent::setBonusArmy(int bonus) {
    this->bonusArmy = bonus;
}

// Deep copy constructor
Continent::Continent(const Continent& continent) {
    continentName = new string(*continent.continentName);
    bonusArmy = continent.bonusArmy;
}

// Deep copy assignment operator
Continent& Continent::operator=(const Continent& continent) {
    if (this != &continent) {
        delete continentName;
        continentName = new string(*continent.continentName);
        bonusArmy = continent.bonusArmy;
    }
    return *this;
}

ostream& operator<<(ostream& outs, Continent& o) {
    outs << "Continent Name: " << *o.continentName << endl;
    outs << "Bonus Army: " << o.bonusArmy << endl;
    return outs;
}

// End of the Continent Class ******************************************************************************************


// Methods implementation of the Map Class ******************************************************************************************
Map::Map() {

}

Map::~Map() {

}

void Map::operator=(Map*) {
    cout << "Maps have no assignment operator!" << endl;
}

void Map::operator+() {
    cout << "Maps cannot be added!" << endl;
}

ostream& operator<<(ostream& os, Map& map) {
    for(auto& kv : map.nodes){
        os << kv.first << " : ";
        for(auto& neighbor : map.edges.at(kv.first)){
            os << neighbor << ",";
        }
        os << endl;
    }
    return os;
}



void Map::addContinent(string Continent_Name, int bonus) {
    this->continents.insert_or_assign(Continent_Name, new Continent(&Continent_Name, bonus));
}

bool Map::territoryInUniqueContinent() {
    // check if every territory in the map belongs to exactly one continent
    int count = 0;

    // for each territory_name and Territory* key-value pair
 
        for (auto& kv : this->nodes) {
            for (auto& c_kv : this->continents) {
            //check if territory_name can be found in exactly one continent
                count += c_kv.second->nodes.count(kv.first);
            }
            // territory name cannot be found or found more than once
            if (count != 1) {
            return false;
            }
            count = 0;
    }
    return true;
}

bool Map::continentsAllSubgraphs() {
    // key represents each continent name in the map; value is a pointer to each continent
    // traversal of all Continents
    for (auto& kv : this->continents) {

        // c_kv represents key-value pairs of the nodes in each continent
        for (auto& c_kv : kv.second->nodes) {

            // first check if all the territory names in a continent can be found in the map
            if (this->nodes.count(c_kv.first) == 0) {

                // if a territory name is not found, then the continent contains a node not in the map
                return false;
            }

            // kv.second: each continent; c_kv.first is each territory name in the continent
            for (auto& name : kv.second->edges.at(c_kv.first)) {

                // this->edges.at(c_kv.first) is the vector of all neighbors of territory c_kv.first
                if (count(this->edges.at(c_kv.first).begin(), this->edges.at(c_kv.first).end(), name) == 0) {
                    // count the vector from begin to end and see the numbers of appearance of name
                    return false;
                }
            }
        }
    }

    return true;
}


bool Map::validate(){
    if(this->isConnected() && this->continentsAllSubgraphs() && this->territoryInUniqueContinent()){
        return true;
    }
    return false;
}
// End of the Map Class ******************************************************************************************