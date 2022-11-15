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

    //C:\Users\3D.map
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

    //game->reinforcementPhase();

 
    Territory *randomTerritory = new Territory();
    for (auto& player : game->getPlayerList()) {
        cout << "ADDING ORDERS" << endl;

        player->getOrdersList()->attach(gameLog);

        Order *blockade = new Blockade(player, randomTerritory);


        player->getOrdersList()->addOrder(blockade);
    }


    for (auto& player : game->getPlayerList()) {
        for (auto& order : (*player->getOrdersList()).order_list) {
            order->attach(gameLog);

            //BUG HERE, STOPS AT VALIDATE() BECAUSE TOATTACK()
            order->execute();
        }
    }
    gameLog->endOutput();


    

}
