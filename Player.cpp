#include "Player.h"
#include "PlayerStrategies.h"

#include <iostream>

using namespace std;
extern Map* worldMap;

// Default constructor
Player::Player()
{
    this->name = "Player";
    this->orderslist = new OrdersList();
    this->hand = new Hand();
    this->territories = vector<Territory*>();
    this->playerStrategy = new HumanPlayerStrategy(this);   // Assumes player is human unless otherwise specified
}

// Non-default constructor accepting a player name
// The Hand and list of territories are created using the setter to avoid ambiguous behavior (infinite loop)
Player::Player(string playerName)
{
    this->name = playerName;
    this->orderslist = new OrdersList();
}

// Non-default constructor accepting all members
Player::Player(string playerName, Hand* newHand, OrdersList* newOrdersList, vector<Territory*> newTerritories)
{
    this->name = playerName;
    this->orderslist = newOrdersList;
    this->hand = newHand;
    this->territories = newTerritories;
}

// Destructor deleting all pointer members
Player::~Player()
{
    delete this->orderslist;
    delete this->hand;
    for (int i = 0; i < this->territories.size(); i++)
    {
        delete this->territories[i];
        this->territories[i] = nullptr;
    }
    this->territories.clear();
    delete this->playerStrategy;
}

// Copy constructor
Player::Player(const Player& player)
{
    this->name = player.name;
    this->orderslist = new OrdersList(*(player.orderslist));
    this->hand = new Hand(*(player.hand));
    this->territories = vector<Territory*>(player.territories);
    this->reinforcementPool = player.reinforcementPool;
    this->playerStrategy = player.playerStrategy;
}

// Assignment operator
Player& Player::operator=(const Player& player)
{
    if (&player != this) {
        this->name = player.name;
        this->reinforcementPool = player.reinforcementPool;

        delete this->orderslist;
        delete this->hand;
        delete this->playerStrategy;
        for (int i = 0; i < this->territories.size(); i++)
        {
            delete this->territories[i];
            this->territories[i] = nullptr;
        }
        this->territories.clear();

        this->orderslist = new OrdersList(*(player.orderslist));
        this->hand = new Hand(*(player.hand));
        this->playerStrategy = player.playerStrategy;
        this->territories = vector<Territory*>(player.territories);
    }

    return *this;
}

// name getter returning the name of the player
string Player::getName() const
{
    return name;
}

// ordersList getter returning the player's list of orders
OrdersList* Player::getOrdersList() const
{
    return orderslist;
}

// hand getter returning the player's hand
Hand* Player::getHand()
{
    return hand;
}

// territories getter returning the player's owned countries
vector<Territory*> Player::getTerritories() const
{
    return territories;
}

/**
 * Returns current player strategy
*/
PlayerStrategy* Player::getPlayerStrategy() {
    return playerStrategy;
}

int Player::getReinforcementPool()
{
    return reinforcementPool;
}

// name setter
void Player::setName(string newName)
{
    name = newName;
}

// orderslist setter
void Player::setOrdersList(OrdersList* newList)
{
    this->orderslist = newList;
}

// hand setter
void Player::setHand(Hand* newHand)
{
    this->hand = newHand;
}

// territories setter
void Player::setTerritories(vector<Territory*> newTerritories)
{
    this->territories = newTerritories;
}

/**
 * Sets current player strategy
 *
 * @param newStrategy The new type of strategy this player should follow
*/
void Player::setPlayerStrategy(PlayerStrategy* newStrategy) {
    this->playerStrategy = newStrategy;
}

void Player::addTerritory(Territory* territory) {
    territories.push_back(territory);
}

void Player::removeTerritory(Territory* territory)
{
    for (int i = 0; i < territories.size(); i++)
    {
        if (territories.at(i) == territory)
        {
            territories.erase(territories.begin() + i);
            return;
        }
    }

    cout << "Player: " << this->getName() << " does not own " << territory->getTerritoryName() << endl;
}

void Player::setReinforcementPool(int pool)
{
    this->reinforcementPool = pool;
}

void Player::setTurnCompleted(bool turn)
{
    this->turnCompleted = turn;

    if (turnCompleted) {
        cout << name << " has ended their turn" << endl;
    }
}

bool Player::isTurnCompleted()
{
    return this->turnCompleted;
}

/**
 * Adds a new order to the Player's order list
 *
 * @param newOrder The order to add
*/
void Player::addOrderToList(Order* newOrder) {
    this->orderslist->addOrder(newOrder);
}

/**
 * Gets and returns a card of a certain type from the Player's hand.
 *
 * @param cardType String type of card to look for
 * @return The card if the play has one, NULL otherwise
*/
Card* Player::getCardFromHandIfExists(string cardType) {
    for (Card* card : hand->getHand()) {
        if (card->getType() == cardType) {
            return card;
        }
    }

    return NULL;
}

// orders created adding to the player's orderslist
void Player::issueOrder()
{
    playerStrategy->issueOrder();
}

// helper method to get a specific order which adds to the player's orderslist
void Player::cardOrder(int orderNumber, CardParameters params)
{
    cout << "card order being executed " << orderNumber << endl;
    vector<Territory*> outposts = this->toDefend();
    vector<Territory*> enemies = this->toAttack();

    PlayerStrategy* temp = this->getPlayerStrategy();
    string name = temp->getStrategyAsString();

    Order* newOrder{};
    switch (orderNumber)
    {
    case 1:
    {
        newOrder = new Deploy(this, 10, outposts.at(rand() % outposts.size()));
        break;
    }
    case 2:
    {
        newOrder = new Advance();
        break;
    }
    case 3:
    {
        if(name.find("Benevolent") != std::string::npos){
            cout << "A benevolent player wouldn't bomb another player" << endl;
            break;
        }
        newOrder = new Bomb(this, enemies.at(rand() % enemies.size()));
        break;
    }
    case 4:
    {
        newOrder = new Blockade(this, outposts.at(rand() % outposts.size()));
        break;
    }
    case 5:
    {
        if(name.find("Aggressive") != std::string::npos){
            cout << "An aggressive player wouldn't do this" << endl;
            break;
        }

        if(outposts.size() == 1){
            break;
        }

        Territory* source = outposts.at(rand() % outposts.size());
        Territory* target = outposts.at(rand() % outposts.size());

        while(source == target){
            Territory* target = outposts.at(rand() % outposts.size());
        }

        newOrder = new Airlift(this, source, target, source->getArmyNumber() / 2);
        break;
    }
    case 6:
    {
        if (ge->getPlayerList().size() == 1)
        {
            break;
        }
        
        if(name.find("Aggressive") != std::string::npos){
            cout << "An aggressive doesn't negotiate" << endl;
            break;
        }

        Player* other = ge->getPlayerList().at(rand() % ge->getPlayerList().size());

        while (this->getName() == other->getName())
        {
            other = ge->getPlayerList().at(rand() % ge->getPlayerList().size());
        }
        
        newOrder = new Negotiate(this, other);
        break;
    }
    default:
        cout << "Invalid card type" << endl;
        break;
    }

    if (newOrder != nullptr)
    {
        this->orderslist->addOrder(newOrder);
    }
}

/**
 * Check the number of continent owning bonus armies for the player
 */
int Player::getContinentsBonus()
{
    int bonus = 0;

    // for each continent pointer in the map
    for (auto& kv : worldMap->continents)
    {
        // get a vector of all territories
        vector<Territory*> c_territories = kv.second->getNodesPtr();

        // get the number of territories in the continent
        int count = c_territories.size();

        // for each territory in the continent, try to find it in the player's territory list
        // if found, move onto the next continent territory
        for (auto& c_t : c_territories)
        {
            for (auto& t : this->territories)
            {
                if (c_t == t)
                {
                    count--;
                    break;
                }
            }
        }

        // in the end if all continent territories are found, continent bonus is added
        if (count == 0)
        {
            bonus += kv.second->getBonusArmy();
        }
    }
    return bonus;
}

bool compareArmyNumber(Territory* t1, Territory* t2) {
    return (t1->getArmyNumber() < t2->getArmyNumber());
}
// return a list of arbitrary territories to defend
vector<Territory*> Player::toDefend()
{
    return playerStrategy->toDefend();
}

// return a list of arbitrary territories to attack
vector<Territory*> Player::toAttack()
{
    return playerStrategy->toAttack();
}

// stream operator that prints the player's owned countries
ostream& operator<<(ostream& outs, Player& player)
{
    outs << player.getName()
        << " ("
        << player.playerStrategy->getStrategyAsString()
        << ")'s owned territories: " << endl;

    for (int i = 0; i < player.territories.size(); i++)
    {
        outs << (*player.territories.at(i)->getTerritoryName()) << endl;
    }

    outs << "Reinforcement pool: " << player.getReinforcementPool() << endl;

    outs << "Current Hand: " << endl;

    vector<Card*> playerHand = player.getHand()->getHand();
    if (playerHand.size() == 0) {
        outs << "No cards in hand!" << endl;
    }
    else {
        for (int i = 0; i < playerHand.size(); i++) {
            outs << *(playerHand.at(i)) << endl;
        }
    }

    return outs;
}