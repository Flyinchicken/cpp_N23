
#include "Player.h"
using namespace std;
#include <iostream>

Player::Player()
{
    this->name = nullptr;
}

Player::Player(string *playerName)
{
    this->name = playerName;
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
    // delete this->ownedTerritories;
    // delete this->orders;
    // delete this->hand;
}

ostream &operator<<(ostream &outs, Player &theObject)
{
    outs << theObject.getName() << "'s owned countries: " << endl;
    return outs;
}