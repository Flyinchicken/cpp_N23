#include "GameEngine.h"
#include "GameEngineDriver.h"

/**
 * Starts a new Warzone game via the GameEngine class.
*/
void testGameStates() {
    GameEngine *ge = new GameEngine();

    ge->startNewGame();
    
    delete ge;  
}

/**
 * Demonstrates that within the startupPhase a map is loaded, validated, players are added, and the game is started
*/
void testStartupPhase() {
    GameEngine *ge = new GameEngine();

    ge->startupPhase();
    
    delete ge;
}