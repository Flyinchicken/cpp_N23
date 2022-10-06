#ifndef PLAYER_H
#define PLAYER_H

#include "Orders.h"
#include "Card.h"
#include <string>
#include <list>
#include <vector>
#include <ostream>
using namespace std;

class OrdersList;
class Hand;

class Player
{
private:
  string name;
  friend ostream &operator<<(ostream &outs, Player &theObject);
  OrdersList *orderslist;
  Hand *hand;

public:
  Player();
  ~Player();
  Player(const Player &player);
  Player &operator=(const Player &player);
  Player(string name);
  // vector<Territory*> toDefend();
  // vector<Territory*> toAttack();
  void issueOrder(int orderNumber);

  string getName() const;
  OrdersList getOrdersList() const;
  Hand getHand() const;

  void setName(string name);
  void setOrdersList(OrdersList *list);
  void setHand(Hand *hand);
};
#endif