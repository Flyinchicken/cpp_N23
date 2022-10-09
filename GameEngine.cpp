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
 * Destructor. No pointer to destroy...for now.
 * */
GameEngine::~GameEngine() {
}

/**
 * Copy constructor. Copies over the current game state.
 * */
GameEngine::GameEngine(const GameEngine &engine) {
    this->currentGameState = engine.currentGameState;
}

/**
 * Assignment operator. Copies over the current game state.
 * */
GameEngine &GameEngine::operator = (const GameEngine &engine) {
    this->currentGameState = engine.currentGameState;
    
    return *this;
}

/*
 * Stream insertion operator. Displays the current state of the game.
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
 * Displays a simple welcome message to the user. Used when a new game has commenced.
*/
void GameEngine::displayWelcomeMessage() {
    cout << "Welcome to Warzone!" << endl;
    cout << "Input a valid command string to start navigating through the various states of the game." << endl;
}

/**
 * Displays a farewell message. Used when the user has exited the game via the "end" command.
*/
void GameEngine::displayFarewellMessage() {
    cout << "Farewell!" << endl;
    cout << "We hope to see you attempt world domination again soon!" << endl;
}

/**
 * Displays a victory message. Used when a player has reached the "Win" state.
*/
void GameEngine::displayVictoryMessage() {
    cout << "Congratulations, you've won!" << endl;
    cout << "You can either play a new game or end your ruthless conquest now" << endl;
}

/**
 * Displays the current game state to console. Calls the stream insertion operator since it currently
 * outputs only this.
*/
void GameEngine::displayCurrentGameState() {
    cout << *this << endl;
}

/**
 * Prompts the user for input from the console and returns it.
 * 
 * @returns The user's console input command.
*/
string GameEngine::getUserInput() {
    cout << "Input your next command: ";

    string inputCommand;
    cin >> inputCommand;

    return inputCommand;
}

/**
 * Checks if the input command string is one of the valid command strings.
 * 
 * @param commandString The command string taken from console input
 * @returns If the command string is one of the valid command strings
*/
bool GameEngine::isValidCommandString(string commandString) {
    return std::find(validCommandStrings.begin(), validCommandStrings.end(), commandString) != validCommandStrings.end();
}

/**
 * Checks if the user has input the "end" command while the game is in the "win" state.
 * 
 * @returns If the user has attempted to end the game after winning.
*/
bool GameEngine::hasGameBeenEnded(string commandString) {
    return currentGameState == 7 && commandString == validCommandStrings.back();
}

/**
 * Parses a command string to its numeric/enum representation and changes the game state based both the numeric and string
 * value of the user input.
 * 
 * @param commandString The user input command string from the console
 * @returns Whether or not a state change has taken place. If a change has not occured, it is because the state change
 * was not a valid one.
*/
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

/**
 * Changes the current state of the game based on what the user would like to change the state to. Will
 * only change the state if it is a valid state transition.
 * For example: 
 *      If user has input the command "validatemap" but the current state is "Start", it will reject this change.
 *      If user has input the command "addplayer" when the current state is "playersadded", it will accept this change
 *      (not however in this instance that the current state will simply be set to the same value it previously had).
 * 
 * @param newState The numeric/enum representation of what the new state of the game should be. This is based off what
 *                 command string the user input to the console.
 * @param commandString The command string the user input to console.
*/
bool GameEngine::setGameStateIfValid(GameStates newState, string commandString) {
    switch (currentGameState) {
        case START:
            if (newState == MAPLOADED) {
                currentGameState = newState;
                return true;
            }
            break;
        case MAPLOADED:
            if (newState == MAPLOADED || newState == MAPVALIDATED) {
                currentGameState = newState;
                return true;
            }
            break;
        case MAPVALIDATED:
            if (newState == PLAYERSADDED) {
                currentGameState = newState;
                return true;
            }
            break;
        case PLAYERSADDED:
            if (newState == PLAYERSADDED || (newState == ASSIGNREINFORCEMENTS && commandString != "endexecorders")) {
                currentGameState = newState;
                return true;
            }
            break;
        case ASSIGNREINFORCEMENTS:
            if (newState == ISSUEORDERS) {
                currentGameState = newState;
                return true;
            }
            break;
        case ISSUEORDERS:
            if (newState == ISSUEORDERS || (newState == EXECUTEORDERS && commandString != "execorder")) {
                currentGameState = newState;
                return true;
            }
            break;
        case EXECUTEORDERS:
            if ((newState == EXECUTEORDERS && commandString != "endissueorders") 
                || (newState == ASSIGNREINFORCEMENTS && commandString != "assigncountries") 
                || newState == WIN
            ) {
                currentGameState = newState;
                return true;
            }
            break;
        case WIN:
            if (newState == START) {
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

/**
 * Checks if the current game state is "Win".
 * 
 * @returns Whether or not a player has won
*/
bool GameEngine::hasPlayerWon() {
    return currentGameState == WIN;
}

/**
 * Starts a new game loop that accepts user input from the console and allows them to navigate through the various
 * states of the game.
*/
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
            displayVictoryMessage();
        }

        displayCurrentGameState();
    }

    displayFarewellMessage();
}