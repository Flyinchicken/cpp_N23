#include "PlayerStrategies.h"
#include "Map.h"
#include "Player.h"
#include "CommandProcessing.h"

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

/**
 * Getter used for testing purposes
 * 
 * @returns Player attached to this strategy
*/
Player* PlayerStrategy::getPlayer() {
    return this->player;
}

///
/// HUMAN PLAYER
///

HumanPlayerStrategy::HumanPlayerStrategy(Player *p) : PlayerStrategy(p) {
    commandProcessor = new CommandProcessor();
 }

/**
 * Copy constructor
*/
HumanPlayerStrategy::HumanPlayerStrategy(const HumanPlayerStrategy& strat) : HumanPlayerStrategy(strat.player) {
    cout << "Copy" << endl;
}

HumanPlayerStrategy::~HumanPlayerStrategy() {
    delete commandProcessor;
}

/**
 * Assignment operator.
 * Doesn't delete player since should be managed elsewhere
*/
HumanPlayerStrategy& HumanPlayerStrategy::operator = (const HumanPlayerStrategy& toAssign) {
    if (this != &toAssign) {
        player = toAssign.player;

        delete commandProcessor;
        commandProcessor = toAssign.commandProcessor;
    }    

    return *this;
}

void HumanPlayerStrategy::issueOrder() {
    // TODO: Use command processor??
    // TODO: Make basic input system
}

vector<Territory*> HumanPlayerStrategy::toAttack() {
    // TODO: Sort by what? Lowest army score?
}

vector<Territory*> HumanPlayerStrategy::toDefend() {
    // TODO: Sort by lowest army score?
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

/**
 * Copy constructor
*/
AggressivePlayerStrategy::AggressivePlayerStrategy(const AggressivePlayerStrategy& strat) : PlayerStrategy(strat.player) {
    cout << "Copy" << endl;
}

AggressivePlayerStrategy::~AggressivePlayerStrategy() {
}

/**
 * Assignment operator.
 * Doesn't delete player since should be managed elsewhere
*/
AggressivePlayerStrategy& AggressivePlayerStrategy::operator = (const AggressivePlayerStrategy& toAssign) {
    if (this == &toAssign) {
        return *this;
    }
    
    player = toAssign.player;

    return *this;
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

/**
 * Copy constructor
*/
BenevolentPlayerStrategy::BenevolentPlayerStrategy(const BenevolentPlayerStrategy& strat) : PlayerStrategy(strat.player) {
}

BenevolentPlayerStrategy::~BenevolentPlayerStrategy() {
}

/**
 * Assignment operator.
 * Doesn't delete player since should be managed elsewhere
*/
BenevolentPlayerStrategy& BenevolentPlayerStrategy::operator = (const BenevolentPlayerStrategy& toAssign) {
    if (this == &toAssign) {
        return *this;
    }
    
    player = toAssign.player;

    return *this;
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

/**
 * Constructor takes Player and passes to PlayerStrategy()
*/
NeutralPlayerStrategy::NeutralPlayerStrategy(Player *p) : PlayerStrategy(p) { }

/**
 * Copy constructor
*/
NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy& strat) : PlayerStrategy(strat.player) {
}

/**
 * Empty destructor
*/
NeutralPlayerStrategy::~NeutralPlayerStrategy() {
}

/**
 * Assignment operator.
 * Doesn't delete player since should be managed elsewhere
*/
NeutralPlayerStrategy& NeutralPlayerStrategy::operator = (const NeutralPlayerStrategy& toAssign) {
    if (this == &toAssign) {
        return *this;
    }
    
    player = toAssign.player;

    return *this;
}

/**
 * Doesn't issue any orders
*/
void NeutralPlayerStrategy::issueOrder() {
    // I'll have an uh...uhhhhhhhhhhhhhhhh...
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

/**
 * Constructor takes Player and passes to PlayerStrategy()
*/
CheaterPlayerStrategy::CheaterPlayerStrategy(Player *p) : PlayerStrategy(p) { }

/**
 * Copy constructor
*/
CheaterPlayerStrategy::CheaterPlayerStrategy(const CheaterPlayerStrategy& strat) : PlayerStrategy(strat.player) {
    cout << "Copy" << endl;
}

/**
 * Empty destructor
*/
CheaterPlayerStrategy::~CheaterPlayerStrategy() {
}

/**
 * Assignment operator.
 * Doesn't delete player since should be managed elsewhere
*/
CheaterPlayerStrategy& CheaterPlayerStrategy::operator = (const CheaterPlayerStrategy& toAssign) {
    if (this != &toAssign) {
        player = toAssign.player;
    } 

    return *this;
}

// TODO: The Cheater player should not issue orders. 
// The code in its issueOrder() function should just change the ownership of all its neighboring territories to themself. 
/**
 * Changes ownership for all neighbouring territories and ends turn.
*/
void CheaterPlayerStrategy::issueOrder() {
    vector<Territory*> territoriesToConquer = this->toAttack();

    for (Territory* t : territoriesToConquer) {
        t->setOwner(player);
    }

    player->setTurn(true);
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

/**
 * Cheater player does nothing but absorb other territories
 * 
 * @returns Empty vector
*/
vector<Territory*> CheaterPlayerStrategy::toDefend() {
    return {};
}

/**
 * @returns The type of strategy as a string
*/
string CheaterPlayerStrategy::getStrategyAsString() const {
    return "Cheater Player (bot)";
}

/**
 * Outputs relevant information of the Player strategy.
 * 
 * @returns The strategy as a string
*/
ostream& operator << (ostream& out, const CheaterPlayerStrategy &strategy) {
    out << strategy.getStrategyAsString();

    return out;
}
