//
// Created by xu zhang on 2022-09-24.
//

#include "Territory.h"

Territory::Territory() {
    this->territoryName = nullptr;
    this->territoryX = 0;
    this->territoryY = 0;
    this->territoryArmies = 0;
    this->continent = nullptr;
    this->territoryOwner = nullptr;
    this->territoryNeighbors = nullptr;
}

Territory::Territory(string* territoryName, int* territoryX, int* territoryY, int* territoryArmies, string* continent, string* territoryOwner, vector<string>* territoryNeighbors) {
    this->territoryName = territoryName;
    this->territoryX = territoryX;
    this->territoryY = territoryY;
    this->territoryArmies = territoryArmies;
    this->continent = continent;
    this->territoryOwner = territoryOwner;
    this->territoryNeighbors = territoryNeighbors;
}

Territory::~Territory() {
    delete this->territoryName;
    delete this->territoryX;
    delete this->territoryY;
    delete this->territoryArmies;
    delete this->continent;
    delete this->territoryOwner;
    delete this->territoryNeighbors;
}

string* Territory::getTerritoryName() {
    return this->territoryName;
}

int* Territory::getTerritoryX() {
    return this->territoryX;
}

int* Territory::getTerritoryY() {
    return this->territoryY;
}

int* Territory::getTerritoryArmies() {
    return this->territoryArmies;
}

string* Territory::getContinent() {
    return this->continent;
}

string* Territory::getTerritoryOwner() {
    return this->territoryOwner;
}

vector<string>* Territory::getTerritoryNeighbors() {
    return this->territoryNeighbors;
}

void Territory::setTerritoryName(string* territoryName) {
    this->territoryName = territoryName;
}

void Territory::setTerritoryX(int* territoryX) {
    this->territoryX = territoryX;
}

void Territory::setTerritoryY(int* territoryY) {
    this->territoryY = territoryY;
}

void Territory::setTerritoryArmies(int* territoryArmies) {
    this->territoryArmies = territoryArmies;
}

void Territory::setContinent(string* continent) {
    this->continent = continent;
}

void Territory::setTerritoryOwner(string* territoryOwner) {
    this->territoryOwner = territoryOwner;
}

void Territory::setTerritoryNeighbors(vector<string>* territoryNeighbors) {
    this->territoryNeighbors = territoryNeighbors;
}
