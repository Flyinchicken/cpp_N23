#include "GameEngine.h"

void testGameStates();

int main() {
    testGameStates();
}

/**
 * Starts a new Warzone game via the GameEngine class.
*/
void testGameStates() {
    GameEngine *ge = new GameEngine();
    ge->startNewGame();
    delete ge;  
}