#include "GameEngineDriver.h"
#include "GameEngine.h"
#include "Player.h"
#include <iostream>
#include "MapDriver.h"
#include "Map.h"
#include "OrdersDriver.h"
#include "CardDriver.h"
#include "PlayerDriver.h"
#include "CommandProcessingDriver.h"
#include "LoggingObserverDriver.h"

using namespace std;

std::string filePath = "";
GameEngine *ge = new GameEngine();
Map *worldMap;

int main(int argc, char **argv)
{
    // testCommandProcessor(argc, argv);

    // testLoggingObserver();

    testStartupPhase();

    // testCommandProcessor();

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
}