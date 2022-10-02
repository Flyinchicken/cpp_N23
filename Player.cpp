
#include "Player.h"
#include "Orders.h"
using namespace std;
#include <iostream>

Player::Player()
{
    this->name = nullptr;
    this->orderslist = new OrdersList();
}

Player::Player(const Player& player)
{
    this->name = new string(*(player.name));
    this->orderslist = new OrdersList(*(player.orderslist));
}

Player& Player::operator=(const Player& player)
{
    this->name = new string(*(player.name));
    return *this;
}

Player::Player(string *playerName)
{
    this->name = playerName;
    this->orderslist = new OrdersList();
}

string Player::getName() const
{
    return *name;
}

void Player::setName(string *newName)
{
    this->name = newName;
}

Player::~Player()
{
    delete this->name;
    delete this->orderslist;
    // delete this->ownedTerritories;
    // delete this->hand;
}

void Player::issueOrder(int orderNumber) {
    Order* newOrder{};
    switch (orderNumber) {
    case 1:
        newOrder = new Deploy();
        cout << "Order created: 1. Deploy" << endl;
        break;
    case 2:
        newOrder = new Advance();
        cout << "Order created: 2. Advance" << endl;
        break;
    case 3:
        newOrder = new Bomb();
        cout << "Order created: 3. Bomb" << endl;
        break;
    case 4:
        newOrder = new Blockade();
        cout << "Order created: 4. Blockade" << endl;
        break;
    case 5:
        newOrder = new Airlift();
        cout << "Order created: 5. Airlift" << endl;
        break;
    case 6:
        newOrder = new Negotiate();
        cout << "Order created: 6. Negotiate" << endl;
        break;
    default:
        cout << "Invalid number: " << orderNumber << ". Please choose an order from 1 - 6." << endl;
        break;
    }
    if (newOrder != nullptr) {
        cout << "not null" << endl;
        this->orderslist->push_back(newOrder);
    }
}
ostream &operator<<(ostream &outs, Player &theObject)
{
    outs << theObject.getName() << "'s owned countries: " << endl;
    return outs;
}