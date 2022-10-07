#include "GameEngine.h"

#include <iostream>

/**
 * Default constructor
 * */
GameEngine::GameEngine() {
    this->currentGameState = 0;
    setGameInProgress(true);
}

/**
 * Destructor
 * */
GameEngine::~GameEngine() {
    // Nothing to delete for now
}

/**
 * Copy constructor
 * */
GameEngine::GameEngine(const GameEngine &engine) {
    this->currentGameState = engine.currentGameState;
    this->gameInProgress = engine.gameInProgress;
}

/**
 * Assignment operator
 * */
GameEngine &GameEngine::operator = (const GameEngine &engine) {
    this->currentGameState = engine.currentGameState;
    this->gameInProgress = engine.gameInProgress;
    
    return *this;
}

/*
 * Stream insertion operator
 * */
ostream &operator << (ostream &out, const GameEngine &engine) {
    out << "Current Game State: " << engine.getGameStateAsString() << endl;
    return out;
}

/**
 * Returns the game state as its corresponding string representation
 * 
 * @returns Game state as a string name
 * */
string GameEngine::getGameStateAsString() const {
    switch (currentGameState) {
        case 0:
            return "Start";
            break;
        case 1:
            return "Map Loaded";
            break;
        case 2:
            return "Map Validated";
            break;
        case 3:
            return "Players Added";
            break;
        case 4:
            return "Assign Reinforcements";
            break;
        case 5:
            return "Issue Orders";
            break;
        case 6:
            return "Execute Orders";
            break;
        case 7:
            return "Win";
            break;
        default:
            return "Current Game state is not valid!";
            break;
    }
}

/**
 * Returns current game state.
 * */
int GameEngine::getCurrentGameState() const {
    return currentGameState;
}

/**
 * Transistions the state of the game from one state to another. Will display an error message to console
 * and change nothing if the transition isn't valid acording to the rules of the game.
 * */
void GameEngine::setCurrentGameState(int newGameState) {
    if (isValidStateTransition(newGameState) || !newGameState) {
        currentGameState = newGameState;
    }
    else {
        std::cout << "Not a valid state transition!" << endl;
    }
}

/**
 * Returns if a game is currently in progress or not
 * */
bool GameEngine::isGameInProgress() const {
    return gameInProgress;
}

/**
 * Either starts or ends a game in progress
 * */
void GameEngine::setGameInProgress(bool gameInProgress) {
    this->gameInProgress = gameInProgress;
}

/**
 * Compares a new game state with the current state and makes sure the state transittion is valid
 * according to the rules.
 * */
bool GameEngine::isValidStateTransition(int newGameState) const {
    switch (currentGameState) {
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
            if (newGameState != 6 && newGameState != 7 && newGameState != 4)     // Can input endissueorders w/o a complaint
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
}

/**
 * Makes sure the command string acquired from the console is valid.
 * */
bool GameEngine::isValidCommandString(string commandString) const {
    if (commandString != "loadmap"
        && commandString != "validatemap"
        && commandString != "addplayer"
        && commandString != "assigncountries"
        && commandString != "issueorder"
        && commandString != "endissueorders"
        && commandString != "execorder"
        && commandString != "endexecorders"
        && commandString != "win"
        && commandString != "play"
        && commandString != "end"
    ) {
        return false;
    }

    if (commandString == "endissueorders" && currentGameState == 6) {
        return false;
    }

    return true;
}

/**
 * Processes a command string and can change the state of the game assuming it is valid.
 * */
void GameEngine::processCommandString(string commandString) {
    if (!isValidCommandString(commandString)) {
        std::cout << "Not a valid command string!" << endl;
    }
    else {
        // Change state based on string
        if (commandString == "loadmap")
            setCurrentGameState(1);
        else if (commandString == "validatemap")
            setCurrentGameState(2);
        else if (commandString == "addplayer")
            setCurrentGameState(3);
        else if (commandString == "assigncountries" || commandString == "endexecorders")
            setCurrentGameState(4);
        else if (commandString == "issueorder")
            setCurrentGameState(5);
        else if (commandString == "endissueorders" || commandString == "execorder")
            setCurrentGameState(6);
        else if (commandString == "win")
            setCurrentGameState(7);
        else if (commandString == "play")
            setCurrentGameState(0);
        else if (commandString == "end")
            setGameInProgress(false);
    }    
}

// enum GameEngine::validGameStates {
//     Start,                    0
//     MapLoaded,                1
//     MapValidated,             2
//     PlayersAdded,             3
//     AssignReinforcement,      4
//     IssueOrders,              5
//     ExecuteOrders,            6
//     Win                       7
// };