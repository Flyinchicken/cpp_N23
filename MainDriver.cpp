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

bool processCommandArguments(int argc, char** argv) {
    if (argc < 2)
    {
        cout << "To execute this program you must enter additional arguments in the form -console or -file <filename>" << endl;
        return false;
    }
    string processorType = argv[1];

    if (processorType == "-console") {
        return true;
    }
    else if (processorType == "-file") {
        if (argc < 3)
        {
            cout << "To execute this program you must enter additional arguments in the form -console or -file <filename>" << endl;
            return false;
        }
        else
        {
            filePath = argv[2];

            if (ifstream(filePath).fail()) {
                cout << "File " << filePath << " does not exist!" << endl;
                return false;
            }

            cout << "filepath is: " << filePath << endl;
        }
        return true;
    }
    else  {
        cout << "To execute this program you must enter additional arguments in the form -console or -file <filename>" << endl;
        return false;
    }
}

int main(int argc, char** argv)
{
    // issueorder deploy 50 1t
    // issueorder advance 1t 1c 50
    // if (processCommandArguments(argc, argv)) {
        x = new Deck();
        ge = new GameEngine();
        // This is a test since a test is being run
        realGame = false;
        // testPlayerStrategies();
        ge = new GameEngine();
        testTournament();
    // }
    
}