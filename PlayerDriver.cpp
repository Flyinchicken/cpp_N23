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
    string *name = new string("peppa");
    Player player(name);
    cout << player << endl;
}
