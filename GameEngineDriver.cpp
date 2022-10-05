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
    cout << "To get started, input a valid command string to navigate through all possible states." << endl;

    GameEngine *ge = new GameEngine();
    cout << *ge << endl;

    while (*ge->isGameInProgress) {
        string inputCommand;
        cin >> inputCommand;

        ge->processCommandString(inputCommand);
        cout << *ge << endl;

        if (ge->getCurrentGameState() == 7) {
            cout << "Conglaturation, you're win!" << endl;
        }
    }    
}