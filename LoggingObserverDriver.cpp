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

    game->reinforcementPhase();

    for (auto& player : game->getPlayerList()) {
        OrdersList *orders = player->getOrdersList();
        orders->attach(gameLog);

        Order *bomb = new Bomb();
        Order *deploy = new Deploy();

        orders->addOrder(bomb);
        orders->addOrder(deploy);
    }

    for (auto& player : game->getPlayerList()) {
        for (auto& order : (*player->getOrdersList()).order_list) {
            order->attach(gameLog);

            //BUG HERE, STOPS AT VALIDATE()
            order->execute();
        }
    }

    gameLog->endOutput();
}
