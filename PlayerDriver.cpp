#include "Player.h"
using namespace std;
#include <iostream>

//Test Player object 
void testPlayers()
{
    Player *player = new Player("Peppa");

    player->setHand(new Hand(player));

    cout << "Orders created: " << endl;
    player->issueOrder();
    player->getOrdersList().print();

    cout << "Territories created: " << endl;
    Territory* territory1 = new Territory(new string("territory 1"), new string("continent 1"), 3, false, player);
    Territory* territory2 = new Territory(new string("territory 2"), new string("continent 2"), 2, false, player);
    vector<Territory*> territories;
    territories.push_back(territory1);
    territories.push_back(territory2);
    player->setTerritories(territories);

    cout << *player << endl;

    cout << "Territories to Defend: " << endl;
    player->toDefend();
    cout << "Territories to Attack: " << endl;
    player->toAttack();
}
