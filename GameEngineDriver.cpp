#include "GameEngine.h"
#include "GameEngineDriver.h"

/**
 * Starts a new Warzone game via the GameEngine class.
*/
void testGameStates() {

    ge->startNewGame();
    
    delete ge;  
}

// void testMainGameLoop(){

//     ge->mainGameLoop();
    
//     delete ge; 
// }

void testStartupPhase() {
    
    ge->startupPhase();

    delete ge;
}