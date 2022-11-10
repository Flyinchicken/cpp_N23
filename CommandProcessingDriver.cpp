#include "CommandProcessing.h"
#include "CommandProcessingDriver.h"
#include "GameEngine.h"
#include <iostream>
using std::endl;
using std::cout;
using std::cin;


void testCommandProcessor(int argc, char** argv) {

    CommandProcessor* processor;

    if (argc < 2) {
        cout << "To execute this program you must enter additional arguments in the form -console or -file <filename>" << endl;
        return;
    }
    string processorType = argv[1];

    if (processorType == "-console") {

        processor = new CommandProcessor();

    }
    else if (processorType == "-file") {

        processor = new FileCommandProcessorAdapter();
        if (argc < 3) {
            cout << "To execute this program you must enter additional arguments in the form -console or -file <filename>" << endl;
            return;
        }
        else {
            filePath = argv[2];
            cout << "filepath is: " << filePath << endl;
        }

    }
    else {
        cout << "To execute this program you must enter additional arguments in the form -console or -file <filename>" << endl;
    }

    GameEngine* game = new GameEngine();
    processor->getCommand(); //processor is now perfectly using polymorphism 
    vector<Command*> commands = processor->getCommandsList();

    for (Command* i : commands) {
        if (i->getCommand().find("Opening") == std::string::npos) {
            cout << "========================================" << endl;
            cout << "Command: " << i->getCommand() << endl;
            cout << *game << endl; //print the state of the game
            if (processor->validate(i, game->getCurrentGameState())) {
                cout << "Command is valid in the current state" << endl;
                game->changeStateFromCommand(i->getCommand()); //if the command is valid, change state of game
            }
        }
    }

}