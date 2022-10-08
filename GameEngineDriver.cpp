#include "GameEngine.h"
using namespace std;
#include <iostream>
#include <string>

void testGameStates();

int main() {
    testGameStates();
}

void testGameStates() {
    GameEngine *ge = new GameEngine();
    ge->startNewGame();
    delete ge;  
}