#ifndef PLAYER_H
#define PLAYER_H

#include "Orders.h"
#include <string>
#include <list>
#include <vector>
#include <ostream>
using namespace std;

class OrdersList;

class Player
{
private:
  string *name;
  friend ostream &operator<<(ostream &outs, Player &theObject);
  OrdersList *orderslist;
  // Hand* hand;
public:
  Player();
  ~Player();
  Player(const Player& player);            
  Player& operator=(const Player& player);
  Player(string *name);
  // list<Territory>* toDefend();
  // list<Territory>* toAttack();
  void issueOrder(int orderNumber);

  string getName() const;

  void setName(string *name);
};

#endif