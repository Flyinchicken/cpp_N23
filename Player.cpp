
#include "Player.h"
//using namespace std;
#include <iostream>

Player::Player() {
    //this->totalPlayers = totalPlayers++;
    this->name = nullptr;
}


Player::Player(std::string playerName): name(&playerName) {
    //cout << "Hello world" << endl;
    //this->totalPlayers = totalPlayers++;
    //this->name = &playerName;
} 

string* Player::getName() {
    return this->name;
}

/* ostream& operator<<(ostream &os, Player &player) {
    os << player.getName() << "'s owned countries: " << endl;
} */

Player::~Player() {
    delete this->name;
    //delete this->totalPlayers;
    //delete this->ownedTerritories;
    //delete this->orders;
    //delete this->hand;
}
