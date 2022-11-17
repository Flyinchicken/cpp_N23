#include "PlayerStrategies.h"

ostream& operator << (ostream &out, const PlayerStrategy &strategy) {
    out << strategy.getStrategyAsString();

    return out;
}

///
/// HUMAN PLAYER
///

void HumanPlayerStrategy::issueOrder() {

}

vector<Territory*> HumanPlayerStrategy::toAttack() {

}

vector<Territory*> HumanPlayerStrategy::toDefend() {

}

string HumanPlayerStrategy::getStrategyAsString() const {
    return "Human Player";
}

/// 
/// AGGRESSIVE PLAYER
///

void AggressivePlayerStrategy::issueOrder() {

}

vector<Territory*> AggressivePlayerStrategy::toAttack() {

}

vector<Territory*> AggressivePlayerStrategy::toDefend() {

}

string AggressivePlayerStrategy::getStrategyAsString() const {
    return "Aggressive Player (bot)";
}

///
/// BENEVOLENT PLAYER
///

void BenevolentPlayerStrategy::issueOrder() {

}

vector<Territory*> BenevolentPlayerStrategy::toAttack() {

}

vector<Territory*> BenevolentPlayerStrategy::toDefend() {

}

string BenevolentPlayerStrategy::getStrategyAsString() const {
    return "Benevolent Player (bot)";
}

///
/// NEUTRAL PLAYER
///

void NeutralPlayerStrategy::issueOrder() {

}

vector<Territory*> NeutralPlayerStrategy::toAttack() {

}

vector<Territory*> NeutralPlayerStrategy::toDefend() {

}

string NeutralPlayerStrategy::getStrategyAsString() const {
    return "Neutral Player (bot)";
}

///
/// CHEATER PLAYER
///

void CheaterPlayerStrategy::issueOrder() {

}

vector<Territory*> CheaterPlayerStrategy::toAttack() {

}

vector<Territory*> CheaterPlayerStrategy::toDefend() {

}

string CheaterPlayerStrategy::getStrategyAsString() const {
    return "Cheater Player (bot)";
}