#include "GameEngineDriver.h"

#include <iostream>
#include "MapDriver.h"
#include "OrdersDriver.h"
#include "CardDriver.h"
#include "PlayerDriver.h"
#include "CommandProcessing.h"
#include "GameEngine.h"

using namespace std;
int main()
{
    /*
    //Test CommandProcessor 
    CommandProcessor *cp = new CommandProcessor();
    cp->getCommand();
    //Print the list of commands in the CommandProcessor object 
    for (int i = 0; i < cp->getCommandsList().size(); i++) {
        cout << (cp->getCommandsList().at(i)->getCommand()) << endl;
    }
    */

    FileCommandProcessorAdapter* file = new FileCommandProcessorAdapter();
    file->getCommand();
    vector<Command*> commands = file->getCommandsList();

    for (Command* i: commands)
        cout <<i->getCommand()<<endl;
    
    //CommandProcessor::validate(cp->getCommandsList().at(0), GameStates::START);

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