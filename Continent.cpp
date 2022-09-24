//
// Created by xu zhang on 2022-09-24.
//

#include "Continent.h"

Continent::Continent() {
    this->continentName = nullptr;
    this->continentBonusValue = 0;
    this->continentTerritories = nullptr;
}

Continent::Continent(string* continentName, int* continentBonusValue, vector<string>* continentTerritories) {
    this->continentName = continentName;
    this->continentBonusValue = continentBonusValue;
    this->continentTerritories = continentTerritories;
}

Continent::~Continent() {
    delete this->continentName;
    delete this->continentBonusValue;
    delete this->continentTerritories;
}

string* Continent::getContinentName() {
    return this->continentName;
}

int* Continent::getContinentBonusValue() {
    return this->continentBonusValue;
}

vector<string>* Continent::getContinentTerritories() {
    return this->continentTerritories;
}

void Continent::setContinentName(string* continentName) {
    this->continentName = continentName;
}

void Continent::setContinentBonusValue(int* continentBonusValue) {
    this->continentBonusValue = continentBonusValue;
}

void Continent::setContinentTerritories(vector<string>* continentTerritories) {
    this->continentTerritories = continentTerritories;
}

