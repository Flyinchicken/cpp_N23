#include "Player.h"
using namespace std;
#include <iostream>

void testPlayers();

int main()
{
    testPlayers();
}

void testPlayers()
{
    Player *player = new Player("peppa");
    cout << player << endl;
    (*player).issueOrder(1);
    (*player).issueOrder(2);
    (*player).issueOrder(3);
    (*player).issueOrder(4);
    (*player).issueOrder(5);
    (*player).issueOrder(6);
    (*player).issueOrder(7);

    cout << (*player).getOrdersList() << endl;


    cout << (*player).getHand() << endl;
    

}
