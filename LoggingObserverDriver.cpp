#include "LoggingObserverDriver.h"
#include "Orders.h"
#include "CommandProcessing.h"
#include "GameEngine.h"

Chicken::Chicken()
{
    name = "Test chicken";
    age = 5;
}

Chicken::~Chicken() {}

void Chicken::scream()
{
    cout << "Chicken screaming" << endl;
    notify(this);
}

string Chicken::stringToLog()
{
    return (name + "\n");
}

void testLoggingObserver()
{
    LogObserver *gameLog = new LogObserver();
    /*Chicken* myChicken = new Chicken();
    myChicken->attach(gameLog);
    myChicken->scream();
    myChicken->scream();
    myChicken->scream();
    myChicken->scream();
    myChicken->scream();
    myChicken->scream();
    myChicken->scream();*/


    CommandProcessor *processor = new CommandProcessor();
    processor->attach(gameLog);

    
    GameEngine* game = new GameEngine();
    game->attach(gameLog);

    game->displayCurrentGameState();

    bool inStartup = true;

    while (inStartup)
    {
        Command* nextCommand = processor->getCommand();
        nextCommand->attach(gameLog);
        vector<Command*> commands = processor->getCommandsList();

        if (processor->validate(nextCommand, game->getCurrentGameState()))
        {
            inStartup = game->processCommand(nextCommand);
        }

        cout << nextCommand->getEffect() << endl;
    }


    
    gameLog->endOutput();
}

int main(){
     testLoggingObserver();
 }
