#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <ostream>
using namespace std;

class Player
{
private:
  string *name;
  friend ostream &operator<<(ostream &outs, Player &theObject);
  // list<Territory>* OwnedTerritories;
  // list<Order>* orders;
  // Hand* hand;
public:
  Player();
  ~Player();
  Player(string *name);
  // list<Territory>* toDefend();
  // list<Territory>* toAttack();
  // void issueOrder();

  string getName() const;

  void setName(string *name);
};

#endif