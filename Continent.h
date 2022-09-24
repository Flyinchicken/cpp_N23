//
// Created by xu zhang on 2022-09-24.
//

#ifndef CPP_N23_CONTINENT_H
#define CPP_N23_CONTINENT_H

#include <string>
#include <vector>

using namespace std;

class Continent {
private:
    string* continentName;
    int* continentBonusValue;
    vector<string>* continentTerritories;

public:
    Continent();
    Continent(string* continentName, int* continentBonusValue, vector<string>* continentTerritories);
    ~Continent();

    string* getContinentName();
    int* getContinentBonusValue();
    vector<string>* getContinentTerritories();

    void setContinentName(string* continentName);
    void setContinentBonusValue(int* continentBonusValue);
    void setContinentTerritories(vector<string>* continentTerritories);
};


#endif //CPP_N23_CONTINENT_H
