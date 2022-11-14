
#include <iostream>
#include "Orders.h"
#include "OrdersDriver.h"
#include "Player.h"
#include "Map.h"
#include "MapLoader.h"
#include "GameEngine.h"

using namespace std;

void testOrderExecution()
{
  MapLoader *mapLoader = new MapLoader();

  Map *map = mapLoader->LoadMap("3D.map");

  vector<Player *> player_list;

  Player *player1 = new Player("Player 1");
  player1->setReinforcementPool(10);
  Player *player2 = new Player("Player 2");
  player2->setReinforcementPool(20);

  player_list.push_back(player1);
  player_list.push_back(player2);

  GameEngine *gameEngine = new GameEngine();

  Territory *territory1 = new Territory(new string("territory 1"), new string("continent 1"), 3, false, player1);
  Territory *territory2 = new Territory(new string("territory 2"), new string("continent 2"), 2, false, player1);
  Territory *territory5 = new Territory(new string("territory 5"), new string("continent 2"), 2, false, player1);
  Territory *territory3 = new Territory(new string("territory 3"), new string("continent 1"), 3, false, player2);
  Territory *territory4 = new Territory(new string("territory 4"), new string("continent 2"), 2, false, player2);

  vector<Territory *> territories_player1;
  vector<Territory *> territories_player2;
  territories_player1.push_back(territory1);
  territories_player1.push_back(territory2);
  territories_player1.push_back(territory5);
  player1->setTerritories(territories_player1);
  territories_player2.push_back(territory3);
  territories_player2.push_back(territory4);
  player2->setTerritories(territories_player2);

  map->addNeighbor("territory 1", "territory 2");

  map->addNeighbor("territory 1", "territory 3");


  //    gameEngine->distributeTerritories(map, player_list);
  worldMap = map;
  ge = gameEngine;

  // ge->setPlayerList(player_list);

  ge->reinforcementPhase();

  // Display player list of Territory
  cout << "Player 1 Territories: " << endl;
  for (Territory *territory : player1->getTerritories())
  {
    cout << *territory->getTerritoryName() << endl;
  }
  cout << "Player 2 Territories: " << endl;
  for (Territory *territory : player2->getTerritories())
  {
    cout << *territory->getTerritoryName() << endl;
  }

  Deploy *o3 = new Deploy(player1, 3, territory1);
  Bomb *o5 = new Bomb(player1, territory3);
  Blockade *o6 = new Blockade(player1, territory1);
  Airlift *o7 = new Airlift(player1, territory2, territory5, 2);

    //Test advance Move behavior
    Advance* orderAdvanceMove = new Advance(player1, territory1, territory2, 2);

    cout << "Before advance order execution" << endl;
    cout << "Test VALIDATE" << endl;

    orderAdvanceMove->validate();
    cout << "Test EXECUTE" << endl;

    orderAdvanceMove->execute();

    //Test advance Attack behavior
    Advance* orderAdvanceAttack = new Advance(player1, territory1, territory3, 2);

    cout << "Before advance order execution" << endl;
    cout << "Test VALIDATE" << endl;

    orderAdvanceAttack->validate();
    cout << "Test EXECUTE" << endl;

    orderAdvanceAttack->execute();

    //Test Negotiate
    Negotiate* orderNegotiate = new Negotiate(player1, player2);

    cout << "Before negotiate order execution" << endl;
    cout << "Test VALIDATE" << endl;
    orderNegotiate->validate();

    cout << "Test EXECUTE" << endl;
    orderNegotiate->execute();

    cout << "After negotiate order execution" << endl;

    Advance* orderAdvance = new Advance(player1, territory1, territory3, 2);

    orderAdvance->validate();
    cout << "Here should be invalid since the Negotiate order has been executed" << endl;


  Bomb *o9 = new Bomb(player2, territory5);
  o3->execute();
  o5->execute();
  o6->execute();
  o7->execute();
  o8->execute();
  o9->execute();

}
