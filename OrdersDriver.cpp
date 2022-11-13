
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
  Negotiate *o8 = new Negotiate(player1, player2);
  Bomb *o9 = new Bomb(player2, territory5);
  o3->execute();
  o5->execute();
  o6->execute();
  o7->execute();
  o8->execute();
  o9->execute();

  //  OrdersList ordersList1;
  //  cout << "*********" << endl;
  //  cout << ordersList1 << endl;
  //  cout << "*********" << endl;
  //  // Order *o1 = new Order();
  //  // Order *o2 = new Order(*o1);
  //  Player *p1 = new Player("Player1");
  //  Territory *territory1 = new Territory(new string("territory 1"), new string("continent 1"), 3, false, p1);
  //  Territory *territory2 = new Territory(new string("territory 2"), new string("continent 2"), 2, false, p1);
  //  vector<Territory *> territories;
  //  territories.push_back(territory1);
  //  territories.push_back(territory2);
  //  p1->setTerritories(territories);
  //  Deploy *o3 = new Deploy(p1, 3, territory1);
  //  Advance *o4 = new Advance();
  //  // ordersList1.push_back(o1);
  //  // ordersList1.push_back(o2);
  //  ordersList1.push_back(o3);
  //  ordersList1.push_back(o4);
  //  cout
  //      //      << o1 << endl
  //      //      << o2 << endl
  //      << o3 << endl
  //      << o4 << endl;
  //  cout << "++++++++" << endl;
  //  cout
  //      // << *o1 << *o2
  //      << *o3 << *o4 << endl;
  //  cout << "++++++++" << endl;
  //  cout << ordersList1 << endl;
  //  cout << "*********" << endl;
  //  ordersList1.move(2, 1);
  //  cout << ordersList1 << endl;
  //  cout << "*********" << endl;
  //  // o1->execute();
  //  ordersList1.remove(2);
  //  Bomb *o5 = new Bomb();
  //  Blockade *o6 = new Blockade(p1, territory1);
  //  Airlift *o7 = new Airlift(p1, territory1, territory2, 2);
  //  Negotiate *o8 = new Negotiate();
  //  ordersList1.push_back(o5);
  //  ordersList1.push_back(o6);
  //  ordersList1.remove(2);
  //  ordersList1.push_back(o7);
  //  ordersList1.push_back(o8);
  //  o3->execute();
  //  cout << o3->getId() << endl;
  //  o6->execute();
  //  o7->execute();
  //  // cout << "The Player: " << *(o4->get_player()) << endl;
  //  cout << ordersList1 << endl;
  //  ordersList1.print();
  //  o8->validate();
}
