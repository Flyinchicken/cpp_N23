#include "Player.h"
using namespace std;
#include <iostream>

void testPlayers();

void testPlayers()
{
    string *name = new string("peppa");
    Player player(name);
    cout << player << endl;
    player.issueOrder(1);
    player.issueOrder(2);
    player.issueOrder(3);
    player.issueOrder(4);
    player.issueOrder(5);
    player.issueOrder(6);
    player.issueOrder(7);

}
