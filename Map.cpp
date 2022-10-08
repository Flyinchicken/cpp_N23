//
// Created by xu zhang on 2022-09-24.
//

#include "Map.h"

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


Continent::Continent() {
    this->continentName = "";
    this->bonusArmy = 0;
}

Continent::Continent(string name, int bonus) {
    this->continentName = name;
    this->bonusArmy = bonus;
}

Continent::~Continent(){
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
