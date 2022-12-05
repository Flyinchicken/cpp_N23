#include "GameEngineDriver.h"
#include "GameEngine.h"
#include "Card.h"
#include "Player.h"
#include <iostream>
#include "MapDriver.h"
#include "Map.h"
#include "OrdersDriver.h"
#include "CardDriver.h"
#include "PlayerDriver.h"
#include "CommandProcessingDriver.h"
#include "LoggingObserverDriver.h"
#include "PlayerStrategiesDriver.h"
#include "PlayerStrategies.h"

using namespace std;

std::string filePath = "";
GameEngine* ge;
Map* worldMap;
Deck* x;
bool realGame;

int main(int argc, char** argv)
{

    // Player* test = new Player();
    // PlayerStrategy* temp = new NeutralPlayerStrategy(test);
    // test->setPlayerStrategy(temp);
    // string name = test->getPlayerStrategy()->getStrategyAsString();

    // if(name.find("Neutral") != std::string::npos){
    //     test->setPlayerStrategy(new AggressivePlayerStrategy(test));
    //   }

    //   cout << test->getPlayerStrategy()->getStrategyAsString() << endl ;

    x = new Deck();
    // This is a test since a test is being run
    realGame = false;
    testPlayerStrategies();
    //testOrderExecution();

    // Need file path before creating
    // ge = new GameEngine();
    // ge = new GameEngine();
    // x = new Deck();
    // testLoggingObserver();
    // vector<Territory*> neighbors = worldMap->getNeighboursPtr();
    //testStartupPhase();

    //testMainGameLoop();

    //testStartupPhase();
    //testMainGameLoop();
    // testCommandProcessor();
    //testOrderExecution();
    /*std::cout << "Welcome everyone!" << std::endl;

    // Map Test
    cout << "*** First, demonstrate map load test ***" << endl;
    //testLoadMaps();

    // Game Engine Tests
    std::cout << std::endl
              << "Game Engine Tests Commencing" << std::endl
              << std::endl;

    //testGameStates();

    // OrdersList Test
    cout << "*** Order list test ***" << endl;
    testOrdersLists();

    // Card Test
    cout << "*** Starting the Card test ***" << endl;
    testCards();

    // Player Test
    cout << "*** Starting the Player test ***" << endl;
    testPlayers();*/
    //}
}