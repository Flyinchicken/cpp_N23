#include "PlayerStrategiesDriver.h"
#include "Player.h"

void testPlayerStrategies() {
    // 1 - Different players can be assigned different strategies that lead to different behavior using the Strategy design pattern
    // 2 - The strategy adopted by a player can be changed dynamically during play
    // 3 - The human player makes decisions according to user interaction, and computer players make decisions automatically, which are both implemented using the strategy pattern
    Player *p = new Player();
    PlayerStrategy *ps = new CheaterPlayerStrategy();
    std::cout << *ps << endl;
    ps = new AggressivePlayerStrategy();
    std::cout << *ps << endl;
    ps = new BenevolentPlayerStrategy();
    std::cout << *ps << endl;
    ps = new NeutralPlayerStrategy();
    std::cout << *ps << endl;
    ps = new HumanPlayerStrategy();
    std::cout << *ps << endl;
}