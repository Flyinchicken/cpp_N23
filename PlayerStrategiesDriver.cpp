#include "PlayerStrategiesDriver.h"
#include "PlayerStrategies.h"
#include "Player.h"

#include <iostream>
    using std::cout;
#include <vector>
    using std::vector;

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
    p->setPlayerStrategy(new NeutralPlayerStrategy(p));
    CheaterPlayerStrategy *chester = new CheaterPlayerStrategy(p);
    CheaterPlayerStrategy* chester2 = new CheaterPlayerStrategy(*chester);
    cout << "CHESTER2: " << *(chester2->getPlayer()) << endl;
    PlayerStrategy* chungus = new CheaterPlayerStrategy(*chester2);
    cout << "CHUNGUS: " << *(chungus->getPlayer()) << endl;
    PlayerStrategy* chungus2 = chester;
    cout << "CHUNGUS2: " << *(chungus2->getPlayer()) << endl;

    // Mock game setup
    GameEngine *strategyEngine = new GameEngine();
    strategyEngine->loadMap(new Command("loadmap ./MapFiles/3D.map"));  // Known valid map so won't validate
    strategyEngine->addPlayer(new Command("addplayer StratTester1"));
    strategyEngine->addPlayer(new Command("addplayer StratTester2"));
    strategyEngine->gameStart(new Command("gamestart"));

    vector<Player*> playerList = strategyEngine->getPlayerList();


    // "Conquers" 1t/1c (the bridge between the two players) for StratTester1
    // to get more bang for your buck for toAttack territories
    // vector<Territory*> testAttack = playerList.at(0)->toAttack();
    // testAttack.at(0)->setOwner(playerList.at(0));
    // testAttack = playerList.at(0)->toAttack();
    // cout << "TO ATTACK: " << endl;
    // for (auto ter : testAttack) {
    //     cout << *ter << endl;
    // }

    cout << "--------------" << endl;

    // playerList.at(0)->setPlayerStrategy(new CheaterPlayerStrategy(playerList.at(0)));
    // testAttack = playerList.at(0)->getPlayerStrategy()->toAttack();
    // cout << "TO ATTACK2: " << endl;
    // for (auto ter : testAttack) {
    //     cout << *ter << endl;
    // }
    // cout << *(playerList.at(0)->getPlayerStrategy()) << *(playerList.at(1)->getPlayerStrategy()) << endl;

    // delete ps;
    // cout << *p;
    int turnCount;

    // Human Player demo that demonstrates humans can create orders or play cards via console input
    cout << "-------HUMAN PLAYER DEMO-----------" << endl;
    delete strategyEngine;
    ge = new GameEngine();
    ge->loadMap(new Command("loadmap ./MapFiles/3D.map"));  // Known valid map so won't validate
    ge->addPlayer(new Command("addplayer HumanPlayer1"));
    ge->gameStart(new Command("gamestart"));

    cout << "Today's participants: " << endl;
    playerList = ge->getPlayerList();
    for (Player* p : playerList) {
        p->setPlayerStrategy(new HumanPlayerStrategy(p));
        cout << p->getName() << " (" << *(p->getPlayerStrategy()) << ")" << endl;
    }

    cout << endl << "Mock issue order phase" << endl;
    // Testing, will be removed
    playerList.at(0)->getHand()->addCardToHand(new Card("default", 1, "Card 6999"));
    playerList.at(0)->getHand()->addCardToHand(new Card("default", 3, "Card 212121212121")); 
    playerList.at(0)->getHand()->addCardToHand(new Card("default", 4, "Card 420"));    
    playerList.at(0)->getHand()->addCardToHand(new Card("default", 5, "Card 123"));    
    playerList.at(0)->issueOrder();

    cout << endl << "Display order list" << endl;
    for (Order* o : playerList.at(0)->getOrdersList()->order_list) {
        cout << *o << endl;
    }

    cout << endl << "Conclusion: Nothing is implemented" << endl;
    cout << "-------END HUMAN PLAYER DEMO-----------" << endl;

    // Basic Neutral player demo that demonstrates their natural affinity for warfare
    cout << "-------NEUTRAL PLAYER DEMO (no change)-----------" << endl;
    delete strategyEngine;

    strategyEngine = new GameEngine();
    strategyEngine->loadMap(new Command("loadmap ./MapFiles/3D.map"));  // Known valid map so won't validate
    strategyEngine->addPlayer(new Command("addplayer NeutralPlayer1"));
    strategyEngine->addPlayer(new Command("addplayer NeutralPlayer2"));
    strategyEngine->addPlayer(new Command("addplayer NeutralPlayer3"));
    strategyEngine->gameStart(new Command("gamestart"));
    
    cout << "Today's participants: " << endl;
    playerList = strategyEngine->getPlayerList();
    for (Player* p : playerList) {
        p->setPlayerStrategy(new NeutralPlayerStrategy(p));
        cout << p->getName() << " (" << *(p->getPlayerStrategy()) << ")" << endl;
    }

    cout << endl << "Mock issue order phase (each player issues two orders)" << endl;
    turnCount = 0;
    while (turnCount < 2) {
        for (Player* p : playerList) {
            p->issueOrder();
            cout << p->getName() << " has issued " << turnCount + 1 << " orders" << endl;
        }

        ++turnCount;
    }

    cout << endl << "Mock execute order phase (iterates over each player's order list)" << endl;
    for (Player* p : playerList) {
        cout << p->getName() << "'s order list: " << endl;
        if (p->getOrdersList()->order_list.size() == 0) {
            cout << p->getName() << " has issued no orders" << endl;
        } 
        else {        // Else exists in case something breaks 
            cout << "Error!" << p->getName() << " shouldn't have any orders!" << endl;
        }
    }

    cout << endl << "Conclusion: Neutral players issue no orders" << endl;
    cout << "-------END NEUTRAL PLAYER DEMO-----------" << endl;


    // Cheater player demo
    cout << endl << "-------CHEATER PLAYER DEMO-----------" << endl << endl;
    delete strategyEngine;

    strategyEngine = new GameEngine();
    strategyEngine->loadMap(new Command("loadmap ./MapFiles/3D.map"));  // Known valid map so won't validate
    strategyEngine->addPlayer(new Command("addplayer StratTester1"));
    strategyEngine->addPlayer(new Command("addplayer StratTester2"));
    strategyEngine->gameStart(new Command("gamestart"));
    
    playerList = strategyEngine->getPlayerList();

    playerList.at(0)->setPlayerStrategy(new CheaterPlayerStrategy(playerList.at(0)));
    playerList.at(1)->setPlayerStrategy(new NeutralPlayerStrategy(playerList.at(1)));
    cout << endl << "Today's participants: " << endl;
    cout << playerList.at(0)->getName() << " (" << *(playerList.at(0)->getPlayerStrategy()) << ")" << endl; 
    cout << playerList.at(1)->getName() << " (" << *(playerList.at(1)->getPlayerStrategy()) << ")" << endl; 

    cout << "Inital Player territories: " << endl;
    for (Player* p : playerList) {
        cout << *p << endl;
    }

    cout << endl << "Mock issue order phase (each player issues two orders)" << endl;
    turnCount = 0;
    while (turnCount < 2) {
        for (Player *p : playerList) {  
            p->issueOrder();
            cout << p->getName() << " has issued " << turnCount + 1 << " orders" << endl;
        }

        cout << endl << "Current Player territories: " << endl;
        for (Player* p : playerList) {
            cout << *p << endl;
        }

        ++turnCount;
    }
    
    cout << "Final Player Territories: " << endl;
    for (Player* p : playerList) {
        cout << *p << endl;
    }

    cout << playerList.at(0)->getName() << "'s order list contains: " << endl;
    if (playerList.at(0)->getOrdersList()->order_list.size() == 0) {
        cout << playerList.at(0)->getName() << " has issued no orders" << endl;
    } 
    else {        // Else exists in case something breaks 
        cout << "Error!" << playerList.at(0)->getName() << " shouldn't have any orders!" << endl;
    }

    cout << endl << "Conclusion: Cheater player has taken over every adjacent territory without issuing a single order (because he cheats)" << endl;
    cout << "-------END CHEATER PLAYER DEMO-----------" << endl;
}