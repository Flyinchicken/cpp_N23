#include "GameEngine.h"
#include "GameEngineDriver.h"

/**
 * Starts a new Warzone game via the GameEngine class.
*/
void testGameStates() {

    ge->startNewGame();
    
    delete ge;  
}

void testMainGameLoop(){
    ge->setGameState(ASSIGNREINFORCEMENTS);
    ge->mainGameLoop();
    
}

/**
 * Demonstrates startup phase works
*/
void testStartupPhase() {
    ge->startupPhase();
}

/**
 * Demonstrates tournament works (or doesn't)
*/
void testTournament() {
    ge->startNewGame();
}