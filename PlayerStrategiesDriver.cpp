#include "PlayerStrategiesDriver.h"
#include "PlayerStrategies.h"
#include "Player.h"

#include <iostream>
    using std::cout;
#include <vector>
    using std::vector;
#include <set>
    using std::set;

void testPlayerStrategies() {

    cout << "--------------" << endl;

    // Basic Neutral player demo that demonstrates their natural affinity for warfare
    cout << "-------NEUTRAL PLAYER DEMO (no change)-----------" << endl;
    delete ge;
    ge = new GameEngine();
    ge->loadMap(new Command("loadmap ./MapFiles/3D.map"));  // Known valid map so won't validate
    ge->addPlayer(new Command("addplayer NeutralPlayer1"));
    ge->addPlayer(new Command("addplayer NeutralPlayer2"));
    ge->addPlayer(new Command("addplayer NeutralPlayer3"));
    ge->gameStart(new Command("gamestart"));

    cout << "Today's participants: " << endl;
    vector<Player*> playerList = ge->getPlayerList();
    for (Player* p : playerList) {
        p->setPlayerStrategy(new NeutralPlayerStrategy(p));
        cout << p->getName() << " (" << *(p->getPlayerStrategy()) << ")" << endl;
    }

    cout << endl << "Mock issue order phase (each player issues two orders)" << endl;
    int turnCount = 0;
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

    // Aggressive player demo that demonstrates their natural affinity for warfare
    cout << "-------AGGRESSIVE PLAYER DEMO-----------" << endl;
    delete ge;

    ge = new GameEngine();
    ge->loadMap(new Command("loadmap ./MapFiles/3D.map"));  // Known valid map so won't validate
    ge->addPlayer(new Command("addplayer AggressivePlayer1"));
    ge->addPlayer(new Command("addplayer AggressivePlayer2"));
    ge->addPlayer(new Command("addplayer AggressivePlayer3"));
    ge->gameStart(new Command("gamestart"));

    cout << "Today's participants: " << endl;
    playerList = ge->getPlayerList();
    for (Player* p : playerList) {
        p->setPlayerStrategy(new AggressivePlayerStrategy(p));
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
        for (Order *p : (*p->getOrdersList()).order_list)
        {
            cout << *p << endl;
        }
    }

    cout << endl << "Conclusion: Aggressive players issue no orders" << endl;
    cout << "-------END AGGRESSIVE PLAYER DEMO-----------" << endl;

    // Benevolent player demo that demonstrates their natural affinity for warfare
    cout << "-------BENEVOLENT PLAYER DEMO-----------" << endl;
    delete ge;

    ge = new GameEngine();
    ge->loadMap(new Command("loadmap ./MapFiles/3D.map"));  // Known valid map so won't validate
    ge->addPlayer(new Command("addplayer BenevolentPlayer1"));
    ge->addPlayer(new Command("addplayer BenevolentPlayer2"));
    ge->addPlayer(new Command("addplayer BenevolentPlayer3"));
    ge->gameStart(new Command("gamestart"));

    cout << "Today's participants: " << endl;
    playerList = ge->getPlayerList();
    for (Player* p : playerList) {
        p->setPlayerStrategy(new BenevolentPlayerStrategy(p));
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
        for (Order *p : (*p->getOrdersList()).order_list)
        {
            cout << *p << endl;
        }
    }

    cout << endl << "Conclusion: Benevolent players issue no orders" << endl;
    cout << "-------END BENEVOLENT PLAYER DEMO-----------" << endl;



    // Cheater player demo
    cout << endl << "-------CHEATER PLAYER DEMO-----------" << endl << endl;
    delete ge;

    ge = new GameEngine();
    ge->loadMap(new Command("loadmap ./MapFiles/3D.map"));  // Known valid map so won't validate
    ge->addPlayer(new Command("addplayer StratTester1"));
    ge->addPlayer(new Command("addplayer StratTester2"));
    ge->gameStart(new Command("gamestart"));
    
    playerList = ge->getPlayerList();

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

    cout << endl << "-------HUMAN PLAYER DEMO-----------" << endl << endl;
    delete ge;
    ge = new GameEngine();
    ge->loadMap(new Command("loadmap ./MapFiles/3D.map"));  // Known valid map so won't validate
    ge->addPlayer(new Command("addplayer HumanPlayer1"));
    ge->addPlayer(new Command("addplayer NeutralPlayer1"));
    ge->gameStart(new Command("gamestart"));
    playerList = ge->getPlayerList();

    cout << "Today's participants: " << endl;
    playerList.at(0)->setPlayerStrategy(new HumanPlayerStrategy(playerList.at(0)));
    playerList.at(1)->setPlayerStrategy(new NeutralPlayerStrategy(playerList.at(1)));
    for (Player* p : playerList) {
        cout << p->getName() << " " << p->getPlayerStrategy()->getStrategyAsString() << endl;
    }

    cout << endl << "Mock issue order phase" << endl;
    // Give human all cards to mess around with
    playerList.at(0)->getHand()->addCardToHand(new Card("default", 1, "Card 6999"));
    playerList.at(0)->getHand()->addCardToHand(new Card("default", 3, "Card 212121212121")); 
    playerList.at(0)->getHand()->addCardToHand(new Card("default", 4, "Card 420"));    
    playerList.at(0)->getHand()->addCardToHand(new Card("default", 5, "Card 123"));
    playerList = ge->getPlayerList();  

    set<string> playersFinished;
    while (playersFinished.size() != playerList.size()) {
        for (Player* p : playerList) {
            if (p->isTurnCompleted()) {
                playersFinished.insert(p->getName());
                continue;
            }

            if (playerList.at(0)->isTurnCompleted() && playerList.at(1)->isTurnCompleted()) {
                break;
            }
            
            p->issueOrder();            
        }
    } 

    cout << endl << "Execute orders" << endl;
    for (Player *i : playerList)
    {
        for (Order *p : (*i->getOrdersList()).order_list)
        {
            p->execute();
        }
    }

    for (Player* p : playerList) {
        cout << p->getName() << " is a " << p->getPlayerStrategy()->getStrategyAsString() << endl;
    }

    cout << "---------END TEST---------" << endl;


    cout << "---------BOT PLAYERS TEST---------" << endl;
    ge = new GameEngine();
    ge->loadMap(new Command("loadmap ./MapFiles/3D.map"));  // Known valid map so won't validate
    ge->addPlayer(new Command("addplayer BenevolentPlayer"));
    ge->addPlayer(new Command("addplayer NeutralPlayer1"));
    ge->addPlayer(new Command("addplayer AggressivePlayer"));
    ge->addPlayer(new Command("addplayer CheaterPlayer"));
    ge->gameStart(new Command("gamestart"));
    playerList = ge->getPlayerList();

    cout << "Today's participants: " << endl;
    playerList.at(0)->setPlayerStrategy(new BenevolentPlayerStrategy(playerList.at(0)));
    playerList.at(1)->setPlayerStrategy(new NeutralPlayerStrategy(playerList.at(1)));
    playerList.at(2)->setPlayerStrategy(new AggressivePlayerStrategy(playerList.at(2)));
    playerList.at(3)->setPlayerStrategy(new CheaterPlayerStrategy(playerList.at(3)));
    for (Player* p : playerList) {
        cout << *p << endl;
    }

    cout << endl << "Mock issue order phase (issue 2 orders)" << endl;
    turnCount = 0;
    while (turnCount < 2) {
        for (Player* p : playerList) {
            p->issueOrder();
            cout << p->getName() << " has issued " << turnCount + 1 << " orders" << endl;
        }

        ++turnCount;
    }

    cout << endl << "Show orders" << endl;
    for (Player *i : playerList)
    {
        cout << *i << endl;
        cout << "ORDERS: " << endl;
        for (Order *p : (*i->getOrdersList()).order_list)
        {
            cout << *p << endl;
        }
        cout << endl;
    }
}