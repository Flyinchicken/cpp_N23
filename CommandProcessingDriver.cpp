#include "CommandProcessing.h"
#include "CommandProcessingDriver.h"
#include "GameEngine.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

void testCommandProcessor(int argc, char **argv)
{

    CommandProcessor* processor = new CommandProcessor();

    if (argc < 2)
    {
        cout << "To execute this program you must enter additional arguments in the form -console or -file <filename>" << endl;
        return;
    }
    string processorType = argv[1];

    if (processorType == "-console")
    {

        processor = new CommandProcessor();
    }
    else if (processorType == "-file")
    {

        processor = new FileCommandProcessorAdapter();
        if (argc < 3)
        {
            cout << "To execute this program you must enter additional arguments in the form -console or -file <filename>" << endl;
            return;
        }
        else
        {
            filePath = argv[2];
            cout << "filepath is: " << filePath << endl;
        }
    }
    else
    {
        cout << "To execute this program you must enter additional arguments in the form -console or -file <filename>" << endl;
    }

    GameEngine *game = new GameEngine();
    game->displayCurrentGameState();
    
    bool gameInProgress = true;

    while (gameInProgress)
    {
        cout << "Input your next command: " << endl;
        Command *nextCommand = processor->getCommand();

        if (processor->validate(nextCommand, game->getCurrentGameState())) {
            game->changeStateFromCommand(nextCommand);
        }

        cout << nextCommand->getEffect() << endl;

        if (nextCommand->getCommand() == CommandStrings::quit) {
            gameInProgress = false;
            game->displayFarewellMessage();
            continue;
        }

        game->displayCurrentGameState();

        if (game->getCurrentGameState() == ASSIGNREINFORCEMENTS) {
            cout << "Simulating a Warzone game..." 
                << endl 
                << "Congratulations! All signs point to your victory, oh glorious one." 
                << endl;

            game->setGameState(WIN);

            game->displayCurrentGameState();
        }
    }    
}