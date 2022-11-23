#include "PlayerStrategies.h"
#include "Map.h"
#include "Player.h"

#include <vector>
#include <iostream>
#include <string>

using std::vector;
using std::string;
using std::ostream;

///
/// PLAYER STRATEGY
///

/**
 * Uses polymorphism to display the type of Strategy this is
*/
ostream& operator << (ostream &out, const PlayerStrategy &strategy) {
    out << strategy.getStrategyAsString();

    return out;
}

/**
 * Constructor that takes a Player and sets the player pointer this Strategy is associated with
 * 
 * No default constructor since Player is needed for toAttack and toDefend.
 * 
 * @param p The player this strategy is assocuated with
*/
PlayerStrategy::PlayerStrategy(Player *p) {
    this->player = p;
}

/**
 * Basic destructor
*/
PlayerStrategy::~PlayerStrategy() {
    delete this->player;
}

///
/// HUMAN PLAYER
///

HumanPlayerStrategy::HumanPlayerStrategy(Player *p) : PlayerStrategy(p) { }

HumanPlayerStrategy::~HumanPlayerStrategy() {
}

void HumanPlayerStrategy::issueOrder() {

}

vector<Territory*> HumanPlayerStrategy::toAttack() {

}

vector<Territory*> HumanPlayerStrategy::toDefend() {

}

string HumanPlayerStrategy::getStrategyAsString() const {
    return "Human Player";
}

ostream& operator << (ostream& out, const HumanPlayerStrategy &strategy) {
    out << strategy.getStrategyAsString();

    return out;
}

/// 
/// AGGRESSIVE PLAYER
///

AggressivePlayerStrategy::AggressivePlayerStrategy(Player *p) : PlayerStrategy(p) { }

AggressivePlayerStrategy::~AggressivePlayerStrategy() {
}

void AggressivePlayerStrategy::issueOrder() {

}

vector<Territory*> AggressivePlayerStrategy::toAttack() {

}

vector<Territory*> AggressivePlayerStrategy::toDefend() {

}

string AggressivePlayerStrategy::getStrategyAsString() const {
    return "Aggressive Player (bot)";
}

ostream& operator << (ostream& out, const AggressivePlayerStrategy &strategy) {
    out << strategy.getStrategyAsString();

    return out;
}

///
/// BENEVOLENT PLAYER
///

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player *p) : PlayerStrategy(p) { }

BenevolentPlayerStrategy::~BenevolentPlayerStrategy() {
}

void BenevolentPlayerStrategy::issueOrder() {

}

vector<Territory*> BenevolentPlayerStrategy::toAttack() {

}

vector<Territory*> BenevolentPlayerStrategy::toDefend() {

}

string BenevolentPlayerStrategy::getStrategyAsString() const {
    return "Benevolent Player (bot)";
}

ostream& operator << (ostream& out, const BenevolentPlayerStrategy &strategy) {
    out << strategy.getStrategyAsString();

    return out;
}

///
/// NEUTRAL PLAYER
///

NeutralPlayerStrategy::NeutralPlayerStrategy(Player *p) : PlayerStrategy(p) { }

NeutralPlayerStrategy::~NeutralPlayerStrategy() {
}

/**
 * Doesn't issue any orders
*/
void NeutralPlayerStrategy::issueOrder() {

}

/**
 * @returns Empty vector since will not attack anything
*/
vector<Territory*> NeutralPlayerStrategy::toAttack() {
    return {};
}

/**
 * @returns Empty vector since will not attack anything
*/
vector<Territory*> NeutralPlayerStrategy::toDefend() {
    return {};
}

string NeutralPlayerStrategy::getStrategyAsString() const {
    return "Neutral Player (bot)";
}

ostream& operator << (ostream& out, const NeutralPlayerStrategy &strategy) {
    out << strategy.getStrategyAsString();

    return out;
}

///
/// CHEATER PLAYER
///

CheaterPlayerStrategy::CheaterPlayerStrategy(Player *p) : PlayerStrategy(p) { }

CheaterPlayerStrategy::~CheaterPlayerStrategy() {
}

void CheaterPlayerStrategy::issueOrder() {

}

/**
 * @returns List of territories the player can attack
*/
vector<Territory*> CheaterPlayerStrategy::toAttack() {
    return getAdjacentEnemyTerritories();
}

/**
 * Gets all enemy territoties adjacent to the player's own territories.
 * Results are not ordered since a Cheater player will conquer all these anyway, regardless
 * of army (a true hero).
 * 
 * @returns Vector of all adjacent enemy territories
*/
vector<Territory*> CheaterPlayerStrategy::getAdjacentEnemyTerritories() {
    vector<Territory*> playerTerritories = this->player->getTerritories();
    vector<Territory*> a_territories;
    set<Territory*> a_set;
    
    for (int i = 0; i < playerTerritories.size(); i++)
    {
        vector<Territory*> temp = worldMap->getNeighboursPtr(*(playerTerritories.at(i)->getTerritoryName()));
        for(auto& neighbor : temp){
            if(neighbor->getOwner() != this->player){
                a_set.insert(neighbor);
            }
        }
    }

    for(auto& neighbor : a_set){
        a_territories.push_back(neighbor);
    }

    return a_territories;
}

// Doesn't defend?
vector<Territory*> CheaterPlayerStrategy::toDefend() {
    return {};
}

string CheaterPlayerStrategy::getStrategyAsString() const {
    return "Cheater Player (bot)";
}

ostream& operator << (ostream& out, const CheaterPlayerStrategy &strategy) {
    out << strategy.getStrategyAsString();

    return out;
}
