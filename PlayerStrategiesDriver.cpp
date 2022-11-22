#include "PlayerStrategiesDriver.h"
#include "PlayerStrategies.h"
#include "Player.h"

void testPlayerStrategies() {
    // 1 - Different players can be assigned different strategies that lead to different behavior using the Strategy design pattern
    // 2 - The strategy adopted by a player can be changed dynamically during play
    // 3 - The human player makes decisions according to user interaction, and computer players make decisions automatically, which are both implemented using the strategy pattern
    Player *p = new Player();
    PlayerStrategy *ps = new CheaterPlayerStrategy(p);
    p->setPlayerStrategy(ps);
    std::cout << *ps << endl;
    std::cout << *p << endl;
    ps = new AggressivePlayerStrategy(p);
    std::cout << *ps << endl;
    std::cout << *p << endl;
    ps = new BenevolentPlayerStrategy(p);
    std::cout << *ps << endl;
    std::cout << *p << endl;
    ps = new NeutralPlayerStrategy(p);
    std::cout << *ps << endl;
    std::cout << *p << endl;
    ps = new HumanPlayerStrategy(p);
    p->setPlayerStrategy(ps);
    std::cout << *ps << endl;
    std::cout << *p << endl;

    GameEngine *strategyEngine = new GameEngine();
    strategyEngine->loadMap(new Command("loadmap ./MapFiles/3D.map"));  // Known valid map so won't validate
    strategyEngine->addPlayer(new Command("addplayer StratTester1"));
    strategyEngine->addPlayer(new Command("addplayer StratTester2"));
     strategyEngine->gameStart(new Command("gamestart"));
    vector<Territory*> testAttack = strategyEngine->playerList.at(0)->toAttack();
    cout << "TERS" << endl;
    for (auto ter : testAttack) {
        // cout << *ter << endl;
        ter->setOwner(strategyEngine->playerList.at(0));
    }
    vector<Territory*> testAttack2 = strategyEngine->playerList.at(0)->toAttack();
    testAttack2.at(0)->setOwner(strategyEngine->playerList.at(0));
    vector<Territory*> testAttack3 = strategyEngine->playerList.at(0)->toAttack();
    for (auto ter : testAttack3) {
        cout << *ter << endl;
    }
}