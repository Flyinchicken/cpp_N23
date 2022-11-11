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

void testMainGameLoop(){
    GameEngine *ge = new GameEngine();

    ge->mainGameLoop();
    
    delete ge; 
}

void testStartupPhase() {
    GameEngine *ge = new GameEngine();

    ge->startupPhase();

    delete ge;
}