
#include "Player.h"
#include "Orders.h"
#include "Map.h"

using namespace std;
#include <iostream>

//Default constructor
Player::Player()
{
    this->name = "Player";
    this->orderslist = new OrdersList();
    this->hand = new Hand();
    this->territories = vector<Territory*>();
}

//Non-default constructor accepting a player name
//The Hand and list of territories are created using the setter to avoid ambiguous behavior (infinite loop)
Player::Player(string playerName)
{
    this->name = playerName;
    this->orderslist = new OrdersList();
}

//Non-default constructor accepting all members
Player::Player(string playerName, Hand* newHand, OrdersList* newOrdersList, vector<Territory*> newTerritories)
{
    this->name = playerName;
    this->orderslist = newOrdersList;
    this->hand = newHand;
    this->territories = newTerritories;
}

//Destructor deleting all pointer members
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

//Copy constructor
Player::Player(const Player &player)
{
    this->name = player.name;
    this->orderslist = new OrdersList(*(player.orderslist));
    this->hand = new Hand(*(player.hand));
    this->territories = vector<Territory*>(player.territories);
}

//Assignment operator
Player &Player::operator=(const Player &player)
{
    this->name = player.name;
    this->orderslist = new OrdersList(*(player.orderslist));
    this->hand = new Hand(*(player.hand));
    this->territories = vector<Territory*>(player.territories);

    return *this;
}

//name getter returning the name of the player
string Player::getName() const
{
    return name;
}

//ordersList getter returning the player's list of orders
OrdersList Player::getOrdersList() const
{
    return *orderslist;
}

//hand getter returning the player's hand
Hand Player::getHand() const
{
    return *hand;
}

//territories getter returning the player's owned countries
vector<Territory*> Player::getTerritories() const
{
    return territories;
}

//name setter
void Player::setName(string newName)
{
    name = newName;
}

//orderslist setter
void Player::setOrdersList(OrdersList *newList)
{
    this->orderslist = newList;
}

//hand setter
void Player::setHand(Hand *newHand)
{
    this->hand = newHand;
}

//territories setter
void Player::setTerritories(vector<Territory*> newTerritories)
{
    this->territories = newTerritories;
}

//orders created adding to the player's orderslist
void Player::issueOrder()
{
    Deploy *deploy = new Deploy();
    Advance* advance = new Advance();
    Bomb* bomb = new Bomb();
    Blockade* blockade = new Blockade();
    Airlift* airlift = new Airlift();
    Negotiate* negotiate = new Negotiate();

    this->orderslist->push_back(deploy);
    this->orderslist->push_back(advance);
    this->orderslist->push_back(bomb);
    this->orderslist->push_back(blockade);
    this->orderslist->push_back(airlift);
    this->orderslist->push_back(negotiate);
}

//helper method to get a specific order which adds to the player's orderslist
void Player::cardOrder(int orderNumber)
{
    Order* newOrder{};
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

//return a list of arbitrary territories to defend
vector<Territory*> Player::toDefend() {
    Territory* t1 = new Territory(new string("territoryTD 1"), new string("continentTD 1"), 3, false, this);
    Territory* t2 = new Territory(new string("territoryTD 2"), new string("continentTD 2"), 3, false, this);
    vector<Territory*> territories;
    territories.push_back(t1);
    territories.push_back(t2);

    for (int i = 0; i < territories.size(); i++) {
        cout << (*territories.at(i)->getTerritoryName()) << endl;
    }
    return territories;
}

//return a list of arbitrary territories to attack
vector<Territory*> Player::toAttack() {
    Territory* t1 = new Territory(new string("territoryTA 1"), new string("continentTA 1"), 3, false, this);
    Territory* t2 = new Territory(new string("territoryTA 2"), new string("continentTA 2"), 3, false, this);
    vector<Territory*> territories;
    territories.push_back(t1);
    territories.push_back(t2);
    for (int i = 0; i < territories.size(); i++) {
        cout << (*territories.at(i)->getTerritoryName()) << endl;
    }
    return territories;
}

//stream operator that prints the player's owned countries
ostream &operator<<(ostream &outs, Player &player)
{
    outs << player.getName() << "'s owned territories: " << endl;

    for (int i = 0; i < player.territories.size(); i++) {
        outs << (*player.territories.at(i)->getTerritoryName()) << endl;
    }

    return outs;
}