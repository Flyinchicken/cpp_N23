
#include "Player.h"
#include "Orders.h"
using namespace std;
#include <iostream>

Player::Player()
{
    name = "Player";
    this->orderslist = new OrdersList();
    this->hand = new Hand();
}

Player::~Player()
{
    delete this->orderslist;
    // delete this->ownedTerritories;
    delete this->hand;
}

Player::Player(const Player &player)
{
    name = player.name;
    this->orderslist = new OrdersList(*(player.orderslist));
    this->hand = new Hand(*(player.hand));
}

Player &Player::operator=(const Player &player)
{
    name = player.name;
    this->orderslist = new OrdersList(*(player.orderslist));
    this->hand = new Hand(*(player.hand));
    return *this;
}

Player::Player(string playerName)
{
    name = playerName;
    this->orderslist = new OrdersList();
    this->hand = new Hand();
}

string Player::getName() const
{
    return name;
}

OrdersList Player::getOrdersList() const
{
    return *orderslist;
}

Hand Player::getHand() const
{
    return *hand;
}

void Player::setName(string newName)
{
    name = newName;
}

void Player::setOrdersList(OrdersList *newList)
{
    this->orderslist = newList;
}

void Player::setHand(Hand *newHand)
{
    this->hand = newHand;
}

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
ostream &operator<<(ostream &outs, Player &theObject)
{
    outs << theObject.getName() << "'s owned countries: " << endl;
    return outs;
}