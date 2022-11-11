#include "GameEngineDriver.h"

#include "Player.h"
#include <iostream>
#include "MapDriver.h"
#include "OrdersDriver.h"
#include "CardDriver.h"
#include "PlayerDriver.h"
#include "CommandProcessingDriver.h"
#include "LoggingObserverDriver.h"

using namespace std;

string filePath = "";

int main(int argc, char** argv)
{
    vector<int> numbers {10, 20, 30, 50, 120, 40, 60, 20, 90, 100};
    
    vector<int> numbers1 = numbers;
    reverse(numbers1.begin(), numbers1.end());
    
    vector<int>::iterator it = find(numbers.begin(), numbers.end(), 20); //Tries to find the Card inside the card by assigning an itetator to the index
    vector<int>::iterator it1 = find(numbers1.begin(), numbers1.end(), 20); //Tries to find the Card inside the card by assigning an itetator to the index

    if (it != numbers.end()) { //If the card is found
        cout << it - numbers.begin() << endl;
    }
    
    if (it1 != numbers1.end()) { //If the card is found
        cout << numbers.size() - 1 - (it1 - numbers1.begin()) << endl;
    }

    //testCommandProcessor(argc, argv);

    //testLoggingObserver();

    //testStartupPhase();

    //testCommandProcessor();

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