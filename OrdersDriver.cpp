#include <iostream>
#include "Orders.h"

using namespace std;

int main()
{
  OrdersList ordersList1;
  cout << "*********" << endl;
  cout << ordersList1 << endl;
  cout << "*********" << endl;
  Order *o = new Order();
  Order *o1 = new Order(*o);
  Order *o2 = new Order();
  Order *o3 = new Order();
  ordersList1.push_back(o);
  ordersList1.push_back(o1);
  ordersList1.push_back(o2);
  ordersList1.push_back(o3);
  cout << o << endl
       << o1 << endl
       << o2 << endl
       << o3 << endl;
  cout << "++++++++" << endl;
  cout << *o << *o1 << *o2 << *o3 << endl;
  cout << "++++++++" << endl;
  cout << ordersList1 << endl;
  cout << "--------" << endl;
  ordersList1.move(2, 1);
  cout << ordersList1 << endl;
  cout << "========" << endl;
  o->execute();
  ordersList1.remove(2);
  Order *o4 = new Order();
  ordersList1.push_back(o4);
  cout << ordersList1 << endl;
  ordersList1.print();
}