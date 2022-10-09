//
// Created by xu zhang on 2022-09-24.
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
