#include "GameEngine.h"

#include <iostream>
#include <algorithm>

/**
 * Default constructor
 * */
GameEngine::GameEngine() {
    this->currentGameState = START;
    validCommandStrings = { 
        "loadmap",
        "validatemap",
        "addplayer",
        "assigncountries",
        "issueorder",
        "endissueorders",
        "execorder",
        "endexecorders",
        "win",
        "play",
        "end"
    };
}

/**
 * Destructor
 * */
GameEngine::~GameEngine() {
}

/**
 * Copy constructor
 * */
GameEngine::GameEngine(const GameEngine &engine) {
    this->currentGameState = engine.currentGameState;
}

/**
 * Assignment operator
 * */
GameEngine &GameEngine::operator = (const GameEngine &engine) {
    this->currentGameState = engine.currentGameState;
    
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
        case START:
            return "Start";
            break;
        case MAPLOADED:
            return "Map Loaded";
            break;
        case MAPVALIDATED:
            return "Map Validated";
            break;
        case PLAYERSADDED:
            return "Players Added";
            break;
        case ASSIGNREINFORCEMENTS:
            return "Assign Reinforcements";
            break;
        case ISSUEORDERS:
            return "Issue Orders";
            break;
        case EXECUTEORDERS:
            return "Execute Orders";
            break;
        case WIN:
            return "Win";
            break;
        default:
            return "Current Game state is not valid!";
            break;
    }
}

/**
 * Displays a simpl welcome message to the user when a new game has commenced.
*/
void GameEngine::displayWelcomeMessage() {
    cout << "Welcome to Warzone!" << endl;
    cout << "Input a valid command string to start navigating through the various states of the game." << endl;
}

void GameEngine::displayFarewellMessage() {
    cout << "Farewell!" << endl;
    cout << "We hope to see you attempt world domination again soon!" << endl;
}

void GameEngine::displayVictoryMessag() {
    cout << "Congratulations, you've won!" << endl;
    cout << "You can either play a new game or end your ruthless conquest now" << endl;
}

void GameEngine::displayCurrentGameState() {
    cout << *this << endl;
}

string GameEngine::getUserInput() {
    cout << "Input your next command: ";

    string inputCommand;
    cin >> inputCommand;

    return inputCommand;
}

bool GameEngine::isValidCommandString(string commandString) {
    return std::find(validCommandStrings.begin(), validCommandStrings.end(), commandString) != validCommandStrings.end();
}

bool GameEngine::hasGameBeenEnded(string commandString) {
    return currentGameState == 7 && commandString == validCommandStrings.back();
}

bool GameEngine::changeStateFromCommand(string commandString) {
    if (commandString == "end") {
        return false;
    }

    if (commandString == "loadmap") {
        return setGameStateIfValid(MAPLOADED, commandString);
    } else if (commandString == "validatemap") {
        return setGameStateIfValid(MAPVALIDATED, commandString);
    } else if (commandString == "addplayer") {
        return setGameStateIfValid(PLAYERSADDED, commandString);
    } else if (commandString == "assigncountries" || commandString == "endexecorders") {
        return setGameStateIfValid(ASSIGNREINFORCEMENTS, commandString);
    } else if (commandString == "issueorder") {
        return setGameStateIfValid(ISSUEORDERS, commandString);
    } else if (commandString == "endissueorders" || commandString == "execorder") {
        return setGameStateIfValid(EXECUTEORDERS, commandString);
    } else if (commandString == "win") {
        return setGameStateIfValid(WIN, commandString);
    } else if (commandString == "play") {
        return setGameStateIfValid(START, commandString);
    } else {
        cout << "Command string is invalid after being checked for validity!" << endl;
        return false;
    }
}

bool GameEngine::setGameStateIfValid(GameStates newState, string commandString) {
    switch (currentGameState) {
        case 0:
            if (newState == 1) {
                currentGameState = newState;
                return true;
            }
            break;
        case 1:
            if (newState == 1 || newState == 2) {
                currentGameState = newState;
                return true;
            }
            break;
        case 2:
            if (newState == 3) {
                currentGameState = newState;
                return true;
            }
            break;
        case 3:
            if (newState == 3 || (newState == 4 && commandString != "endexecorders")) {
                currentGameState = newState;
                return true;
            }
            break;
        case 4:
            if (newState == 5) {
                currentGameState = newState;
                return true;
            }
            break;
        case 5:
            if (newState == 5 || (newState == 6 && commandString != "execorder")) {
                currentGameState = newState;
                return true;
            }
            break;
        case 6:
            if ((newState == 6 && commandString != "endissueorders") || newState == 4 || newState == 7) {
                currentGameState = newState;
                return true;
            }
            break;
        case 7:
            if (newState == 0) {
                currentGameState = newState;
                cout << "Starting new game..." << endl;
                return true;
            }
            break;
        default:
            cout << "Current state is not valid!" << endl;
    }

    return false;
}

bool GameEngine::hasPlayerWon() {
    return currentGameState == 7;
}

void GameEngine::startNewGame() {
    displayWelcomeMessage();

    bool isGameInProgress = true;

    while (isGameInProgress) {
        string inputCommand = getUserInput();

        if (!isValidCommandString(inputCommand)) {
            cout << inputCommand << " is not a valid command string!" << endl;
            continue;
        }

        if (hasGameBeenEnded(inputCommand)) {
            isGameInProgress = false;
            continue;
        }

        if (!changeStateFromCommand(inputCommand)) {
            cout << "Invalid state transition!" << endl;
        }
        else if (hasPlayerWon()) {                          // In "else if" so displays only once if user decides to input jargin after claiming victory
            displayVictoryMessag();
        }

        displayCurrentGameState();
    }

    displayFarewellMessage();
}