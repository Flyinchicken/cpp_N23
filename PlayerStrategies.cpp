#include "PlayerStrategies.h"
#include "Map.h"
#include "Player.h"
#include "CommandProcessing.h"
#include "Orders.h"

#include <vector>
#include <iostream>
#include <string>

using std::vector;
using std::string;
using std::ostream;
using std::cout;
using std::cin;
using std::isdigit;
using std::stoi;

///
/// PLAYER STRATEGY
///

/**
 * Free function to compare army numbers between two territories, decreasing order 
*/
bool compareArmyNumberDecrease(Territory* t1, Territory* t2){
    return (t1->getArmyNumber() < t2->getArmyNumber());
}

/**
 * Free function to compare army numbers between two territories, increasing order 
*/
bool compareArmyNumberIncrease(Territory* t1, Territory* t2){
    return (t1->getArmyNumber() > t2->getArmyNumber());
}

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

/**
 * Determines if a string is an int/number.
 * 
 * From: https://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
 * 
 * @returns bool indicating if string is a number
*/
bool PlayerStrategy::isStringNumber(string input) {
    std::string::const_iterator iterator = input.begin();

    while (iterator != input.end() && isdigit(*iterator)) {
        ++iterator;
    }

    return !input.empty() && iterator == input.end();
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
    // Create order or play card
    // loop until set turn
    // set turn = setTurnCompleted
    // getTurn = isTurnCompleted?
    while (!player->isTurnCompleted()) {
        cout << "Beep boop I am a human that is issueing an order" << endl;
        cout << endl << "\t Valid commands:" << endl
            << "\t issueorder deploy <num_armyunits> <target_territory>" << endl
            << "\t issueorder advance <source_territory> <target_territory> <num_armyunits>" << endl
            << "\t issueorder bomb" << endl
            << "\t issueorder blockade" << endl
            << "\t issueorder airlift" << endl
            << "\t issueorder negotiate" << endl << endl;
        vector<Territory*> playerTerritories = player->getTerritories();
        cout << "\t Player territories:"  << endl;
        for (Territory* t : playerTerritories) {
            cout << "\t" << *t->getTerritoryName() << endl;
        }
        /*
        1. Territories of toAttack
        2. Territories of toDefend
        3. World map
        4. See deck
        5. See reinforcement pool
        6. See current territories
        7. issue an order
        */
        // int displayOption;
        // cin >> displayOption;
        // if (displayOption >= 1 && displayOption <= 7) {
        //     processInputOption(displayOption);
        // }
        // else {
        //     cout << displayOption << " is not a valid input. Please input a nummber between 1 and 7." << endl;
        //     continue;
        // }
        
        // 1 get issueing orders working
        // 2 dispay options

        Command* nextCommand = commandProcessor->getCommand();
        vector<string> splitCommand = commandProcessor->splitStringByDelim(nextCommand->getCommand(), ' ');
        string commandKeyword = splitCommand.front();

        if (commandKeyword == CommandStrings::issueOrdersEnd) {
            player->setTurnCompleted(true);
            cout << player->getName() << " has ended their turn" << endl;
            continue;
        }

        if (commandKeyword != CommandStrings::issueOrder) {
            cout << "Issue orders using the \"issueorder\" keyword. \""
                << commandKeyword << "\" is not valid"
                << endl;
            nextCommand->saveEffect("Command doesn't include issueorder keyword");
            continue;
        }

        if (splitCommand.size() < 2) {
            cout << "Please specify an order type!" << endl;
            continue;
        }

        string commandType = splitCommand.at(1);

        // issueorder deploy <armyunits> <territory>
        if (commandType == "deploy") {
            if (splitCommand.size() != 4) {
                cout << "Deploy order must be formatted as: issueorder deploy <num_armyunits> <target_territory>" << endl;
                continue;
            }

            if (!isStringNumber(splitCommand.at(2))) {
                cout << splitCommand.at(2) << " is not a valid number!" << endl;
                continue;
            }

            int numArmyToDeploy = stoi(splitCommand.at(2));
            Territory* targetTerritory = worldMap->getNode(splitCommand.at(3));

            if (targetTerritory == NULL) {
                cout << "Could not find territory with name " << splitCommand.at(3) << " in world map" << endl;
                continue;
            }

            //check if input territory is a player's territory
            bool isOwnedTerritory = false;
            for (Territory* t : playerTerritories) {
                string *territory = t->getTerritoryName();
                if (*territory == *targetTerritory->getTerritoryName()) {
                    isOwnedTerritory = true;
                    break;
                }
            }

            if (!isOwnedTerritory) {
                cout << "Target territory " << splitCommand.at(3) << " is not owned by player " << player->getName() << endl;
                continue;
            }


            player->addOrderToList(new Deploy(player, numArmyToDeploy, targetTerritory));
            cout << "DEPLOYED" << endl;
        }
        // issueorder advance <source_territory> <target_territory> <armyunits>
        else if (commandType == "advance") {
            if (splitCommand.size() != 5) {
                cout << "Advance order must be formatted as: issueorder advance <source_territory> <target_territory> <num_armyunits>" << endl;
                continue;
            }

            Territory* sourceTerritory = worldMap->getNode(splitCommand.at(2));
            if (sourceTerritory == NULL) {
                cout << "Could not find territory with name " << splitCommand.at(2) << " in world map" << endl;
                continue;
            }

            Territory* targetTerritory = worldMap->getNode(splitCommand.at(3));
            if (targetTerritory == NULL) {
                cout << "Could not find territory with name " << splitCommand.at(3) << " in world map" << endl;
                continue;
            }

            if (!isStringNumber(splitCommand.at(4))) {
                cout << splitCommand.at(4) << " is not a valid number!" << endl;
                continue;
            }
            int numArmyToDeploy = stoi(splitCommand.at(4));

            player->addOrderToList(new Advance(player, sourceTerritory, targetTerritory, numArmyToDeploy));
            cout << "ADVANCED" << endl;
        }
        // issueorder bomb <target_territory>
        else if (commandType == "bomb") {
            cout << "BOMBD" << endl;
        }
        // issueorder blockade <target_territory>
        else if (commandType == "blockade") {
            cout << "BLOCKADED" << endl;
        }
        // issueorder airlift <source_territory> <target_territory> <armyunits>
        else if (commandType == "airlift") {
            cout << "AIRLIFTED" << endl;
        }
        // issueorder negotiate <target_player>
        else if (commandType == "negotiate") {
            cout << "NEGOTIATED" << endl;
        }
        else {
            cout << commandType << " is not a valid command type!" << endl;
        }
    }
}

vector<Territory*> HumanPlayerStrategy::toAttack() {
    // TODO: Sort by what? Lowest army score?
    return {};
}

vector<Territory*> HumanPlayerStrategy::toDefend() {
    // TODO: Sort by lowest army score?
    return {};
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
    // deploy all armies to the strongest territory
    int numToDeploy = player->getReinforcementPool();
    vector<Territory*> d_territories = this->toDefend();
    Territory* target = d_territories.at(0);
    player->addOrderToList(new Deploy(player, numToDeploy, target));

    vector<Territory*> a_territories = this->toAttack();
    // for each territory owned by the player, take all of its armies and advance to all possible toAttack territories
    for(int i = 0; i < player->getTerritories().size(); i++){
        for(auto& a_t : a_territories){
            player->addOrderToList(new Advance(player, player->getTerritories().at(i), a_t, player->getTerritories().at(i)->getArmyNumber() - 1));
        }
    }

    // use all possible aggressive cards to all possible toAttack territories
    for(auto& a_t : a_territories){
            player->addOrderToList(new Bomb(player, a_t));
    }

    player->setTurnCompleted(true);
}

vector<Territory*> AggressivePlayerStrategy::toAttack() {
    vector<Territory*> a_territories;
    set<Territory*> a_set;
    
    for (int i = 0; i < player->getTerritories().size(); i++)
    {
        vector<Territory*> temp = worldMap->getNeighboursPtr(*(player->getTerritories().at(i)->getTerritoryName()));
        for(auto& neighbor : temp){
            if(neighbor->getOwner() != player){
                a_set.insert(neighbor);
            }
        }
    }

    for(auto& neighbor : a_set){
        a_territories.push_back(neighbor);
    }

    sort(a_territories.begin(),a_territories.end(), compareArmyNumberIncrease);

    return a_territories;
}

// Return vector of territories belong to the player in decreasing order, the first territory in the vector will be the strongest
vector<Territory*> AggressivePlayerStrategy::toDefend() {
    vector<Territory*> d_territories;
    for (int i = 0; i < player->getTerritories().size(); i++)
    {
        d_territories.push_back(player->getTerritories().at(i));
    }

    sort(d_territories.begin(),d_territories.end(), compareArmyNumberDecrease);
    return d_territories;
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
    return {};
}

vector<Territory*> BenevolentPlayerStrategy::toDefend() {
    return {};
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
 * Doesn't issue any orders so just ends turn
*/
void NeutralPlayerStrategy::issueOrder() {
    // I'll have an uh...uhhhhhhhhhhhhhhhh...
    player->setTurnCompleted(true);
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

    player->setTurnCompleted(true);
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
