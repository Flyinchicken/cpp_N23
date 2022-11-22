#include "PlayerStrategies.h"
#include "Map.h"

ostream& operator << (ostream &out, const PlayerStrategy &strategy) {
    out << strategy.getStrategyAsString();

    return out;
}

PlayerStrategy::PlayerStrategy(Player *p) {
    this->player = p;
}

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

vector<Territory*> CheaterPlayerStrategy::toAttack() {

}

vector<Territory*> CheaterPlayerStrategy::getAdjacentEnemyTerritories() {
    
}

vector<Territory*> CheaterPlayerStrategy::toDefend() {

}

string CheaterPlayerStrategy::getStrategyAsString() const {
    return "Cheater Player (bot)";
}

ostream& operator << (ostream& out, const CheaterPlayerStrategy &strategy) {
    out << strategy.getStrategyAsString();

    return out;
}
