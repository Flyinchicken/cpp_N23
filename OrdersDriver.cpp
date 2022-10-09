
#include <iostream>
#include "Orders.h"

using namespace std;

void testOrdersLists()
{
    OrdersList ordersList1;
    cout << "*********" << endl;
    cout << ordersList1 << endl;
    cout << "*********" << endl;
    Order* o1 = new Order();
    Order* o2 = new Order(*o1);
    Deploy* o3 = new Deploy();
    Advance* o4 = new Advance();
    ordersList1.push_back(o1);
    ordersList1.push_back(o2);
    ordersList1.push_back(o3);
    ordersList1.push_back(o4);
    cout << o1 << endl
        << o2 << endl
        << o3 << endl
        << o4 << endl;
    cout << "++++++++" << endl;
    cout << *o1 << *o2 << *o3 << *o4 << endl;
    cout << "++++++++" << endl;
    cout << ordersList1 << endl;
    cout << "*********" << endl;
    ordersList1.move(2, 1);
    cout << ordersList1 << endl;
    cout << "*********" << endl;
    o1->execute();
    ordersList1.remove(2);
    Bomb* o5 = new Bomb();
    Blockade* o6 = new Blockade();
    Airlift* o7 = new Airlift();
    Negotiate* o8 = new Negotiate();
    ordersList1.push_back(o5);
    ordersList1.push_back(o6);
    ordersList1.push_back(o7);
    ordersList1.push_back(o8);
    o7->execute();
    cout << ordersList1 << endl;
    ordersList1.print();
    o8->validate();
}