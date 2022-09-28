#include "GameEngine.h"
using namespace std;
#include <iostream>
#include <string>

void testGameStates();

int main() {
    testGameStates();
}

void testGameStates() {
    cout << "Welcome to Warzone!" << endl;

    GameEngine *ge = new GameEngine("Start");

    cout << *ge;

    GameEngine *ge2 = ge;

    cout << *ge2;
}