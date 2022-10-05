#include <iostream>
#include <vector>
#include <unordered_map>
#include "Map.h"
#include <string>

// Add a node to the graph
void Graph::addNode(std::string name, Territory* territory){
    this->nodes->insert_or_assign(name,territory);
}

// Add a neighbor to the existing node
void Graph::addNeighbor(std::string name, std::string neighbor){
    this->edges->at(name)->push_back(neighbor);
}

// search by name and return a node
Territory* Graph::getNode(std::string name){
    return this->nodes->at(name);

}

// search by name of the territory and return a vector containing all of its neighbors
std::vector<std::string>* Graph::getNeighbours(std::string name){
    return this->edges->at(name);
}


bool validate(){
    // always return true for now
    return true;
}