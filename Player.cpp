
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

void Player::issueOrder(int orderNumber)
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
        cout << "Invalid number: " << orderNumber << ". Please choose an order from 1 - 6." << endl;
        break;
    }
    if (newOrder != nullptr)
    {
        cout << (*newOrder) << endl;
        this->orderslist->push_back(newOrder);
    }
}
ostream &operator<<(ostream &outs, Player &theObject)
{
    outs << theObject.getName() << "'s owned countries: " << endl;
    return outs;
}