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

    // Mock game setup
    GameEngine *strategyEngine = new GameEngine();
    strategyEngine->loadMap(new Command("loadmap ./MapFiles/3D.map"));  // Known valid map so won't validate
    strategyEngine->addPlayer(new Command("addplayer StratTester1"));
    strategyEngine->addPlayer(new Command("addplayer StratTester2"));
    strategyEngine->gameStart(new Command("gamestart"));

    vector<Player*> playerList = strategyEngine->getPlayerList();


    // "Conquers" 1t/1c (the bridge between the two players) for StratTester1
    // to get more bang for your buck for toAttack territories
    vector<Territory*> testAttack = playerList.at(0)->toAttack();
    testAttack.at(0)->setOwner(playerList.at(0));
    testAttack = playerList.at(0)->toAttack();
    cout << "TO ATTACK: " << endl;
    for (auto ter : testAttack) {
        cout << *ter << endl;
    }

    cout << "--------------" << endl;

    playerList.at(0)->setPlayerStrategy(new CheaterPlayerStrategy(playerList.at(0)));
    testAttack = playerList.at(0)->getPlayerStrategy()->toAttack();
    cout << "TO ATTACK2: " << endl;
    for (auto ter : testAttack) {
        cout << *ter << endl;
    }
    cout << *(playerList.at(0)->getPlayerStrategy()) << *(playerList.at(1)->getPlayerStrategy()) << endl;

    // delete ps;
    // cout << *p;
}