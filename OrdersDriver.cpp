
#include <iostream>
#include "Orders.h"
#include "OrdersDriver.h"
#include "Player.h"
#include "Map.h"

using namespace std;

void testOrdersLists()
{
  OrdersList ordersList1;
  cout << "*********" << endl;
  cout << ordersList1 << endl;
  cout << "*********" << endl;
  // Order *o1 = new Order();
  // Order *o2 = new Order(*o1);
  Player *p1 = new Player("Player1");
  Territory *territory1 = new Territory(new string("territory 1"), new string("continent 1"), 3, false, p1);
  Territory *territory2 = new Territory(new string("territory 2"), new string("continent 2"), 2, false, p1);
  vector<Territory *> territories;
  territories.push_back(territory1);
  territories.push_back(territory2);
  p1->setTerritories(territories);
  Deploy *o3 = new Deploy(p1, 3, territory1);
  Advance *o4 = new Advance();
  // ordersList1.push_back(o1);
  // ordersList1.push_back(o2);
  ordersList1.push_back(o3);
  ordersList1.push_back(o4);
  cout
      //      << o1 << endl
      //      << o2 << endl
      << o3 << endl
      << o4 << endl;
  cout << "++++++++" << endl;
  cout
      // << *o1 << *o2
      << *o3 << *o4 << endl;
  cout << "++++++++" << endl;
  cout << ordersList1 << endl;
  cout << "*********" << endl;
  ordersList1.move(2, 1);
  cout << ordersList1 << endl;
  cout << "*********" << endl;
  // o1->execute();
  ordersList1.remove(2);
  Bomb *o5 = new Bomb();
  Blockade *o6 = new Blockade(p1, territory1);
  Airlift *o7 = new Airlift(p1, territory1, territory2, 2);
  Negotiate *o8 = new Negotiate();
  ordersList1.push_back(o5);
  ordersList1.push_back(o6);
  ordersList1.remove(2);
  ordersList1.push_back(o7);
  ordersList1.push_back(o8);
  o3->execute();
  cout << o3->getId() << endl;
  o6->execute();
  o7->execute();
  // cout << "The Player: " << *(o4->get_player()) << endl;
  cout << ordersList1 << endl;
  ordersList1.print();
  o8->validate();
}
