#include "Player.h"
using namespace std;
#include <iostream>

void testPlayers();

int main()
{
    Player *player = new Player("peppa");
    cout << *player << endl;
    (*player).issueOrder();


    cout << (*player).getOrdersList() << endl;


    cout << (*player).getHand() << endl;
    

}
