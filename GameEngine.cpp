#include "GameEngine.h"

#include <iostream>

/**
 * Default constructor
 * */
GameEngine::GameEngine() {
    this->currentGameState = new int(0);
}

/**
 * Destructor
 * */
GameEngine::~GameEngine() {
    delete this->currentGameState;
}

/**
 * Copy constructor
 * */
GameEngine::GameEngine(const GameEngine &engine) {
    this->currentGameState = new int(*engine.currentGameState);
}

/**
 * Assignment operator
 * */
GameEngine &GameEngine::operator=(const GameEngine &engine) {
    // Do something
    return *this;
}

/*
 * Stream insertion operator
 * */
ostream &operator << (ostream &out, const GameEngine &engine) {
    out << "Current Game State: " << *engine.currentGameState << endl;
    return out;
}

/**
 * Returns current game state.
 * */
int GameEngine::getCurrentGameState() {
    return *currentGameState;
}

/**
 * Sets the current game state to something new.
 * 
 * Checks first that the new game state transition is valid, and, if it isn't, returns -1, else returns the value of the 
 * current state after transitioning.
 * */
int GameEngine::setCurrentGameState(int newGameState) {
    if (!isValidStateTransition(newGameState)) {
        return -1;
    }

    *currentGameState = newGameState;
    return *currentGameState;
}

bool GameEngine::isValidStateTransition(int newGameState) {
    switch (*currentGameState) {
        case 0:
            if (newGameState != 1)
                return false;
            break;
        case 1:
            if (newGameState != 1 && newGameState != 2)
                return false;
            break;
        case 2:
            if (newGameState != 3) 
                return false;
            break;
        case 3:
            if (newGameState != 3 && newGameState != 4)
                return false;
            break;
        case 4:
            if (newGameState != 5)
                return false;
            break;
        case 5:
            if (newGameState != 5 && newGameState != 6)
                return false;
            break;
        case 6:
            if (newGameState != 6 && newGameState != 7)
                return false;
            break;
        case 7:
            if (newGameState != 0)
                return false;
            break;
        default:
            std::cout << "Not a valid state transition!" << endl;
            break;
    }

    return true;
    // // Places where loops are accepted:
    // // mapLoaded, playersAdded, issueOrders, executeOrders
    // if ((newGameState - *currentGameState == 0) 
    //     && (*currentGameState == 1 || *currentGameState == 3 || *currentGameState == 5 || *currentGameState == 6)) {
    //         // This should be ok
    // }

    // // 2 Exceptions to this:
    // // Go from win to start
    // // Go from executeorders to assign
    // if ((newGameState - *currentGameState != 1) 
    //     || (newGameState - *currentGameState != -7)) {
    //     return false;
    // }
    
    // return true;
}

void GameEngine::processCommandString(string commandString) {
    // Check to make sure is a valid command string
}

// // enum GameEngine::validGameStates {
// //     Start,                    0
// //     MapLoaded,                1
// //     MapValidated,             2
// //     PlayersAdded,             3
// //     AssignReinforcement,      4
// //     IssueOrders,              5
// //     ExecuteOrders,            6
// //     Win                       7
// // };

// /**
//  * Default constructor
//  * */
// GameEngine::GameEngine() {
//     this->currentGameState = nullptr;
// }

// /**
//  * Destructor
//  * */
// GameEngine::~GameEngine() {
//     delete this->currentGameState;
// }

// /**
//  * Get current game state
//  * */
// int* GameEngine::getCurrentGameState() {
//     return this->currentGameState;
// }

// /**
//  * Copy constructor
//  * */
// GameEngine::GameEngine(const GameEngine &copy) {
//     this->currentGameState = copy.currentGameState;
// }

