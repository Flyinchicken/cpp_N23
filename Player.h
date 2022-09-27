#ifndef PLAYER_H
#define PLAYER_H

using namespace std;
#include <string>
#include <vector>
#include <ostream>

class Player
{
  private:
    string* name;
    friend ostream& operator<<(ostream&, const Player&);
    //list<Territory>* OwnedTerritories;
    //list<Order>* orders;
    //Hand* hand;
  public:
    Player();
    ~Player();
    Player(std::string name);
    static int* totalPlayers;
    //list<Territory>* toDefend();
    //list<Territory>* toAttack();
    void issueOrder();

    string* getName();

    void setName(string* name);
};

#endif


