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
    ge = new GameEngine();
    // This is a test since a test is being run
    realGame = false;
    //testPlayerStrategies();
    testTournament();
}