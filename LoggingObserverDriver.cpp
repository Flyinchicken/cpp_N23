#include "LoggingObserverDriver.h"
#include "Orders.h"
#include "CommandProcessing.h"
#include "GameEngine.h"


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

    game->reinforcementPhaseForLogObserverDriver();

    //Add orders for players
    for (auto& player : game->getPlayerList()) {

        player->getOrdersList()->attach(gameLog);

        vector<Territory*> enemies = player->toAttack();

        //valid, uses enemy territory
        Order *bomb = new Bomb(player, enemies.at(rand() % enemies.size()));

        //invalid, uses ennemy territory instead of own
        Order *blockade = new Blockade(player, enemies.at(rand() % enemies.size()));

        player->getOrdersList()->addOrder(bomb);
        player->getOrdersList()->addOrder(blockade);
    }

    game->setGameState(EXECUTEORDERS);

    //execute the orders for players
    for (auto& player : game->getPlayerList()) {
        for (auto& order : (*player->getOrdersList()).order_list) {
            order->attach(gameLog);
            order->execute();
        }
    }
    gameLog->endOutput();


    

}
