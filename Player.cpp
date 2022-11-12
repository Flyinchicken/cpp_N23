#include "Player.h"

using namespace std;
#include <iostream>
extern Map *worldMap;

// Default constructor
Player::Player()
{
    this->name = "Player";
    this->orderslist = new OrdersList();
    this->hand = new Hand();
    this->territories = vector<Territory *>();
}

// Non-default constructor accepting a player name
// The Hand and list of territories are created using the setter to avoid ambiguous behavior (infinite loop)
Player::Player(string playerName)
{
    this->name = playerName;
    this->orderslist = new OrdersList();
}

// Non-default constructor accepting all members
Player::Player(string playerName, Hand *newHand, OrdersList *newOrdersList, vector<Territory *> newTerritories)
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
}

// Copy constructor
Player::Player(const Player &player)
{
    this->name = player.name;
    this->orderslist = new OrdersList(*(player.orderslist));
    this->hand = new Hand(*(player.hand));
    this->territories = vector<Territory *>(player.territories);
    this->reinforcementPool = player.reinforcementPool;
}

// Assignment operator
Player &Player::operator=(const Player &player)
{
    this->name = player.name;
    this->orderslist = new OrdersList(*(player.orderslist));
    this->hand = new Hand(*(player.hand));
    this->territories = vector<Territory *>(player.territories);
    this->reinforcementPool = player.reinforcementPool;

    return *this;
}

// name getter returning the name of the player
string Player::getName() const
{
    return name;
}

// ordersList getter returning the player's list of orders
OrdersList Player::getOrdersList() const
{
    return *orderslist;
}

// hand getter returning the player's hand
Hand *Player::getHand()
{
    return hand;
}

// territories getter returning the player's owned countries
vector<Territory *> Player::getTerritories() const
{
    return territories;
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
void Player::setOrdersList(OrdersList *newList)
{
    this->orderslist = newList;
}

// hand setter
void Player::setHand(Hand *newHand)
{
    this->hand = newHand;
}

// territories setter
void Player::setTerritories(vector<Territory *> newTerritories)
{
    this->territories = newTerritories;
}

void Player::addTerritory(Territory *territory)
{
    territories.push_back(territory);
}

void Player::removeTerritory(Territory *territory)
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
    this->reinforcementPool = reinforcementPool;
}

void Player::setTurn(bool turn)
{
    this->turnCompleted = turn;
}

// orders created adding to the player's orderslist
void Player::issueOrder()
{
    if (this->getReinforcementPool() > 4)
    {
        this->orderslist->push_back(new Deploy()); // Deploy order, should take certain params
        this->setReinforcementPool(this->getReinforcementPool() - 5);
    }
    else if (this->getReinforcementPool() > 0)
    {
        this->orderslist->push_back(new Deploy()); // Deply order but now with the rest of the reinforcement pool
        this->setReinforcementPool(0);
    }
    else
    {
        vector<Territory *> potentialAttacks = this->toAttack();
        vector<Territory *> outposts = this->toDefend();

        if (potentialAttacks.size() > numAttacks)
        { // If we can attack any territory that we have not yet attacked

            Territory *target = potentialAttacks.at(numAttacks);
            vector<Territory *> adj; // Should be equal to the adjacent territories of target
            for (Territory *p : adj)
            {
                vector<Territory *>::iterator it = find(outposts.begin(), outposts.end(), p); // Tries to find which territory should be the source
                if (it != outposts.end())
                {
                    Territory *source = outposts.at(it - outposts.begin()); // Source territory
                    this->orderslist->push_back(new Advance());
                    numAttacks++;
                    break;
                }
            }
        }
        else
        { // If it can't attack it will try to defend

            vector<Territory *> reinforcers = outposts;
            reverse(reinforcers.begin(), reinforcers.end());
            bool hasDefended = false;

            for (int i = numDefense; i < outposts.size(); i++)
            {

                if (hasDefended)
                {
                    return;
                }

                Territory *target = outposts.at(i);
                vector<Territory *> adj; // Should be equal to the adjacents of target

                for (Territory *tempAdj : adj)
                {
                    vector<Territory *>::iterator it = find(reinforcers.begin(), reinforcers.end(), tempAdj); // Tries to find where it can take troops from to defend from the territory with the most troops
                    if (it != reinforcers.end())
                    {
                        int index = outposts.size() - 1 - (it - reinforcers.begin());
                        if (index > i)
                        {
                            Territory *source = outposts.at(index);
                            this->orderslist->push_back(new Advance()); // Should take source and target as argument
                            hasDefended = true;
                            numDefense = i + 1;
                            break;
                        }
                    }
                }
            }

            if (!this->getHand()->getHand().empty())
            {
                vector<Card *> cards = this->getHand()->getHand();
                cards[0]->play(this->getHand());
            }
            this->setTurn(true);
            finishedPlayers++;
        }
    }
}

// helper method to get a specific order which adds to the player's orderslist
void Player::cardOrder(int orderNumber)
{
    Order *newOrder{};
    switch (orderNumber)
    {
    case 1:
        newOrder = new Deploy();
        break;
    case 2:
        newOrder = new Advance();
        break;
    case 3:
        newOrder = new Bomb();
        break;
    case 4:
        newOrder = new Blockade();
        break;
    case 5:
        newOrder = new Airlift();
        break;
    case 6:
        newOrder = new Negotiate();
        break;
    default:
        cout << "Invalid card type" << endl;
        break;
    }
    if (newOrder != nullptr)
    {
        cout << (*newOrder) << endl;
        this->orderslist->push_back(newOrder);
    }
}

/**
 * Check the number of continent owning bonus armies for the player
 */
int Player::getContinentsBonus()
{
    int bonus = 0;

    // for each continent pointer in the map
    for (auto &kv : worldMap->continents)
    {
        // get a vector of all territories
        vector<Territory *> c_territories = kv.second->getNodesPtr();

        // get the number of territories in the continent
        int count = c_territories.size();

        // for each territory in the continent, try to find it in the player's territory list
        // if found, move onto the next continent territory
        for (auto &c_t : c_territories)
        {
            for (auto &t : this->territories)
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

// return a list of arbitrary territories to defend
vector<Territory *> Player::toDefend()
{
    vector<Territory *> d_territories;
    for (int i = 0; i < territories.size(); i++)
    {
        d_territories.push_back(territories.at(i));
    }
    return d_territories;
}

// return a list of arbitrary territories to attack
vector<Territory *> Player::toAttack()
{
    Territory *t1 = new Territory(new string("territoryTA 1"), new string("continentTA 1"), 3, false, this);
    Territory *t2 = new Territory(new string("territoryTA 2"), new string("continentTA 2"), 3, false, this);
    vector<Territory *> territories;
    territories.push_back(t1);
    territories.push_back(t2);
    for (int i = 0; i < territories.size(); i++)
    {
        cout << (*territories.at(i)->getTerritoryName()) << endl;
    }
    return territories;
}

// stream operator that prints the player's owned countries
ostream &operator<<(ostream &outs, Player &player)
{
    outs << player.getName() << "'s owned territories: " << endl;

    for (int i = 0; i < player.territories.size(); i++)
    {
        outs << (*player.territories.at(i)->getTerritoryName()) << endl;
    }

    return outs;
}