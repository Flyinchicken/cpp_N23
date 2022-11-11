#include "GameEngine.h"
#include "MapLoader.h"

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

/**
 * Default constructor sets current game state to Start
 * */
GameEngine::GameEngine() {
    this->currentGameState = START;
    worldMap = nullptr;

    if (filePath.empty()) {
        this->commandProcessor = new CommandProcessor();
    }
    else {
        this->commandProcessor = new FileCommandProcessorAdapter();
    }
}

/**
 * Destructor. No pointers to destroy...for now.
 * */
GameEngine::~GameEngine() {
    delete this->commandProcessor;

    if (worldMap != nullptr) {
        delete worldMap;
    }
}

/**
 * Copy constructor. Copies over the current game state.
 * */
GameEngine::GameEngine(const GameEngine& engine) {
    this->currentGameState = engine.currentGameState;
}

/**
 * Assignment operator. Copies over the current game state.
 * */
GameEngine& GameEngine::operator = (const GameEngine& engine) {
    this->currentGameState = engine.currentGameState;

    return *this;
}


GameStates GameEngine::getCurrentGameState() {
    return this->currentGameState;
}

/*
 * Stream insertion operator for GameEngine. Displays the current state of the game.
 * */
ostream& operator << (ostream& out, const GameEngine& engine) {
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
        return "Error: current Game state is not valid!";
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
 * Displays a farewell message. Used when the user has exited the game via the "end" command after winning.
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
 * Checks if the user has input the "end" command while the game is in the "win" state.
 *
 * @returns If the user has attempted to end the game after winning.
*/
bool GameEngine::hasGameBeenEnded(string command) {
    return currentGameState == WIN && command == CommandStrings::quit;
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
    if (commandString == CommandStrings::quit) {
        return false;
    }

    if (commandString.find("loadmap") != std::string::npos) {
        this->currentGameState = MAPLOADED;
    }
    else if (commandString == CommandStrings::validateMap) {
        this->currentGameState = MAPVALIDATED;
    }
    else if (commandString.find("addplayer") != std::string::npos) {
        this->currentGameState = PLAYERSADDED;
    }
    else if (commandString == CommandStrings::gameStart) {
        this->currentGameState = ASSIGNREINFORCEMENTS;
    }
    else if (commandString == CommandStrings::replay) {
        this->currentGameState = START;
    }
    else {
        cout << "Error: command string is invalid after being checked for validity!" << endl;
        return false;
    }

    return true;
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
 * Command-based user interaction mechanism to start the game
*/
void GameEngine::startupPhase() {
    bool inStartup = true;

    int lastIndex = -1;

    while (inStartup) {
        commandProcessor->getCommand();

        vector<Command*> commands = commandProcessor->getCommandsList();

        for (int i = lastIndex == -1 ? 0 : lastIndex; i < commands.size(); i++) {
            if (commandProcessor->validate(commands[i], currentGameState)) {
                inStartup = processCommand(commands[i]);
            }

            cout << commands[i]->getEffect() << commands[i]->getCommand() << endl;
        }

        lastIndex = commands.size();
    }
}

/**
 * Processes a Command object and performs any necessary actions and state changes necessary.
 * Assumes the command has already been validated.
 *
 * @param command The command to process
 * @return If the startup phase should continue
*/
bool GameEngine::processCommand(Command* command) {
    string commandString = commandProcessor->splitStringByDelim(command->getCommand(), ' ').front();

    if (commandString == CommandStrings::loadMap) {
        loadMap(command);
    }
    else if (commandString == CommandStrings::validateMap) {
        validateMap(command);
    }
    else if (commandString == CommandStrings::addPlayer) {
        addPlayer(command);
    }
    else if (command->getCommand() == CommandStrings::gameStart) {
        gameStart(command);
        return false;
    }

    return true;
}

/**
 * Loads a map file into the worldMap object
 *
 * @param command The command to save the effect of loading the map into
*/
void GameEngine::loadMap(Command* command) {
    MapLoader mapLoader;
    string mapName = commandProcessor->splitStringByDelim(command->getCommand(), ' ').back();

    worldMap = mapLoader.LoadMap(mapName);

    command->saveEffect("Successfully loaded map file " + mapName + ". State changed to MAPLOADED");

    setGameState(MAPLOADED);
}

/**
 * Validates loaded world map file.
 *
 * @param command The command to save the effect of validating the map into
*/
void GameEngine::validateMap(Command* command) {
    if (worldMap->validate()) {
        setGameState(MAPVALIDATED);
        command->saveEffect("Map was successfully validated. State changed to MAPVALIDATED");
    }
    else {
        command->saveEffect("MAP was not a valid map. No state changes occured");
    }
}

void GameEngine::addPlayer(Command* command) {

}

void GameEngine::gameStart(Command* command) {

}


/**
 * Sets current game state based on input new state.
 *
 * @param newGameState What to change the current game state to
*/
void GameEngine::setGameState(GameStates newGameState) {
    currentGameState = newGameState;
}

/**
 * gamestart command triggers state change to ASSIGNREINFORCEMENT and call mainGameLoop
 * Loop between reinforcement, issuing orders, and execute orders.
*/
void GameEngine::mainGameLoop() {
    //********For Assignement 2 only**********
    currentGameState = ASSIGNREINFORCEMENTS;
    //****************************************
    while (currentGameState != WIN) {
        if (currentGameState == ASSIGNREINFORCEMENTS) {
            reinforcementPhase();
        }
        else if (currentGameState == ISSUEORDERS) {
            issueOrdersPhase();
        }
        else {
            executeOrdersPhase();
        }

    }
}

/**
 * calculate and assign armies to each player
*/
void GameEngine::reinforcementPhase() {

    for (Player* i : playerList) {
        int pool = i->getTerritories().size();
        // INSERT CODE TO SEE IF PLAYER OWNS A CONTINENT AND ADD THE BONUS

        i->setReinforcementPool(pool);
    }
}

void GameEngine::issueOrdersPhase() {

    vector<bool> turnEnded;

    int currentPlayers = playerList.size();
    for (int i = 0; i < currentPlayers; i++)
    {
        turnEnded.push_back(false);
    }

    int finishedPlayers = 0;

    while (finishedPlayers != playerList.size()) {

        for (int i = 0; i < playerList.size(); i++)
        {
            if (turnEnded[i]) {
                continue; //Player has ended turn so we done
            }

            Player* temp = playerList.at(i);

            if (temp->getOrdersList().order_list.size() > 6) {
                if (!temp->getHand()->getHand().empty()) {
                    vector<Card*> cards = temp->getHand()->getHand();
                    cards[0]->play(temp->getHand());
                }
                turnEnded[i] = true;
                finishedPlayers++;
            }

            if (temp->getReinforcementPool() > 4) {
                temp->issueOrder(); //Deploy order, should take certain params
                temp->setReinforcementPool(temp->getReinforcementPool() - 5);
            }
            else if (temp->getReinforcementPool() > 0) {
                temp->issueOrder(); //Deply order but now with the rest of the reinforcement pool
                temp->setReinforcementPool(0);
            }
            else {
                vector<Territory*> potentialAttacks = temp->toAttack();
                if (potentialAttacks.empty())
                {
                    if (!temp->getHand()->getHand().empty()) {
                        vector<Card*> cards = temp->getHand()->getHand();
                        cards[0]->play(temp->getHand());
                    }
                    turnEnded[i] = true;
                    finishedPlayers++;
                }

                vector<string> namesOfTarget;
                for (Territory* i : potentialAttacks) {
                    namesOfTarget.push_back(*i->getTerritoryName());
                }

                vector<Territory*> outposts = temp->toDefend();

                if (!potentialAttacks.empty()) {
                    bool hasAttacked = false;
                    for (Territory* i : outposts) {
                        if (hasAttacked) {
                            break;
                        }

                        vector<string> adj = worldMap->getNeighbours(*i->getTerritoryName());
                        for (string p : adj) {
                            vector<string>::iterator it = find(namesOfTarget.begin(), namesOfTarget.end(), p);
                            if (it != namesOfTarget.end()) {
                                temp->issueOrder(); //Atttack order, should have target and destination territorry
                                hasAttacked = true;
                                break;
                            }
                        }
                    }
                }
            }
        }

    }
}

void GameEngine::executeOrdersPhase() {

    for (Player* i : playerList) {
        for (Order* p : i->getOrdersList().order_list) {
            p->execute();
        }
    }
}


/**
 * Starts a new game loop that accepts user input from the console and allows them to navigate through the various
 * states of the game.
*/
void GameEngine::startNewGame() {
    displayWelcomeMessage();

    displayCurrentGameState();

    bool isGameInProgress = true;

    while (isGameInProgress) {
        // TODO: Move to command processor
        string inputCommand = getUserInput();
        Command* command = new Command(inputCommand);

        if (!this->commandProcessor->validate(command, this->currentGameState)) {
            cout << command->getEffect() << endl;
            displayCurrentGameState();
            continue;
        }

        if (hasGameBeenEnded(command->getCommand())) {
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