/*#include "GameEngineDriver.h"
#include "GameEngine.h"
#include "Player.h"
#include <iostream>
#include "MapDriver.h"
#include "Map.h"
#include "OrdersDriver.h"
#include "CardDriver.h"
#include "PlayerDriver.h"
#include "CommandProcessingDriver.h"*/
#include "LoggingObserverDriver.h"

using namespace std;

std::string filePath = "";
// GameEngine *ge;
// Map *worldMap;

// Deck *x = new Deck();

int main(int argc, char **argv)
{
    // testCommandProcessor(argc, argv);

    // Need file path before creating
    // ge = new GameEngine();

    // testStartupPhase();

    // testMainGameLoop();

    // testOrderExecution();

    testLoggingObserver();
}