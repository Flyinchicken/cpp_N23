//
// Created by xu zhang on 2022-09-24.
// Implemented Map, Continent, Graph methods for validation by Weijie Tan on 2022-10-08
//

#include "Map.h"

// Methods implementation of the Territory Class ******************************************************************************************
Territory::Territory() {
    this->name = "";
    this->continent = "";
    this->armies = 0;
    this->owner = "";
    this->occupied = false;
}

Territory::Territory(string name, string continent, int armies, string owner) {
    this->name = name;
    this->continent = continent;
    this->armies = armies;
    this->owner = owner;
    this->occupied = false;
}

string Territory::getName() const {
    return this->name;
}

string Territory::getContinent() const {
    return this->continent;
}

int Territory::getArmy() const {
    return this->armies;
}

string Territory::getOwner() const {
    return this->owner;
}

bool Territory::isOccupied() const {
    return this->occupied;
}

void Territory::setName(string name) {
    this->name = name;
}

void Territory::setContinent(string continent) {
    this->continent = continent;
}

void Territory::setArmy(int army) {
    this->armies = army;
}

void Territory::setOwner(string owner) {
    this->owner = owner;
}

void Territory::setOccupied(bool occupied) {
    this->occupied = occupied;
}

void Territory::operator+() {
    cout << "Territories cannot be added!" << endl;
}

string Territory::operator<<(Territory*) {
    return "Territory: " + this->getName() + " number of armies: " + to_string(this->getArmy()) + " owned by: " + this->getOwner();
}

void Territory::operator=(Territory*) {
    cout << "Territories have no assignment operator!" << endl;
}
// End of the Territory Class *********************************************************************************************************



// Methods implementation of the Graph Class ******************************************************************************************
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
                neighborStack.push(neighbor);
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


// Methods implementation of the Continent Class ******************************************************************************************
Continent::Continent() {
    this->continentName = "";
    this->bonusArmy = 0;
}

Continent::Continent(string name, int bonus) {
    this->continentName = name;
    this->bonusArmy = bonus;
}

Continent::~Continent() {
    delete this;
}

string Continent::getContinentName() const {
    return this->continentName;
}

int Continent::getBonusArmy() const {
    return this->bonusArmy;
}

void Continent::setContinentName(string name) {
    this->continentName = name;
}

void Continent::setBonusArmy(int bonus) {
    this->bonusArmy = bonus;
}

void Continent::operator+() {
    cout << "Continents cannot be added!" << endl;
}

string Continent::operator<<(Continent*) {
    return "Continent: " + this->getContinentName() + " number of bonus armies: " + to_string(this->getBonusArmy()) + " owned by: " + this->getOwner();
}

void Continent::operator=(Continent*) {
    cout << "Continents have no assignment operator!" << endl;
}
// End of the Continent Class ******************************************************************************************


// Methods implementation of the Map Class ******************************************************************************************
Map::Map() {

}

Map::~Map() {

}

void Map::operator+() {
    cout << "Maps cannot be added!" << endl;
}

string Map::operator<<(Map*) {
    return "This is a game map for RISK";
}

void Map::operator=(Map*) {
    cout << "Maps have no assignment operator!" << endl;
}

void Map::addContinent(string Continent_Name, int bonus) {
    this->continents.at(Continent_Name) = new Continent(Continent_Name, bonus);
}

bool Map::territoryInUniqueContinent() {
    // check if every territory in the map belongs to exactly one continent
    int count = 0;

    // for each territory_name and Territory* key-value pair
    for (auto& kv : this->nodes) {
        for (auto& c_kv : this->continents) {
            //check if territory_name can be found in exactly one continent
            if (c_kv.first == kv.first) {
                count++;
            }

            // a territory belongs to more than 1 continent
            if (count > 1) {
                return false;
            }
        }
        // territory name cannot be found
        if (count != 1) {
            return false;
        }
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
// End of the Map Class ******************************************************************************************