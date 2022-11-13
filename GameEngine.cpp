#include "GameEngine.h"
#include "MapLoader.h"
#include "LoggingObserver.h"
#include <iostream>
#include <string>
#include <sstream>

using std::cin;
using std::cout;
using std::endl;

int finishedPlayers;
int turnNumber = 0;

/**
 * Default constructor sets current game state to Start
 * */
GameEngine::GameEngine()
{
    this->currentGameState = START;
    worldMap = nullptr;

    if (filePath.empty())
    {
        this->commandProcessor = new CommandProcessor();
    }
    else
    {
        this->commandProcessor = new FileCommandProcessorAdapter();
    }
}

/**
 * Destructor. No pointers to destroy...for now.
 * */
GameEngine::~GameEngine()
{
    delete this->commandProcessor;

    if (worldMap != nullptr)
    {
        delete worldMap;
    }
}

/**
 * Copy constructor. Copies over the current game state.
 * */
GameEngine::GameEngine(const GameEngine &engine)
{
    this->currentGameState = engine.currentGameState;
    this->commandProcessor = engine.commandProcessor;
}

/**
 * Assignment operator. Copies over the current game state.
 * */
GameEngine &GameEngine::operator=(const GameEngine &engine)
{
    this->currentGameState = engine.currentGameState;
    this->commandProcessor = engine.commandProcessor;

    return *this;
}

/**
 * @returns The current state of the game
*/
GameStates GameEngine::getCurrentGameState()
{
    return this->currentGameState;
}

/**
 * Stream insertion operator for GameEngine. Displays the current state of the game.
 * */
ostream &operator<<(ostream &out, const GameEngine &engine)
{
    out << "Current Game State: " << engine.getGameStateAsString() << endl;

    return out;
}

/**
 * Returns the game state as its corresponding string representation
 *
 * @returns Game state as a string name
 * */
string GameEngine::getGameStateAsString() const
{
    switch (currentGameState)
    {
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
void GameEngine::displayWelcomeMessage()
{
    cout << "Welcome to Warzone!" << endl;
    cout << "Input a valid command string to start navigating through the various states of the game." << endl;
}

/**
 * Displays a farewell message. Used when the user has exited the game via the "end" command after winning.
 */
void GameEngine::displayFarewellMessage()
{
    cout << "Farewell!" << endl;
    cout << "We hope to see you attempt world domination again soon!" << endl;
}

/**
 * Displays a victory message. Used when a player has reached the "Win" state.
 */
void GameEngine::displayVictoryMessage()
{
    cout << "Congratulations, you've won!" << endl;
    cout << "You can either play a new game or end your ruthless conquest now" << endl;
}

/**
 * Displays the current game state to console. Calls the stream insertion operator since it currently
 * outputs only this.
 */
void GameEngine::displayCurrentGameState()
{
    cout << *this << endl;
}

/**
 * Checks if the user has input the "end" command while the game is in the "win" state.
 *
 * @returns If the user has attempted to end the game after winning.
 */
bool GameEngine::hasGameBeenEnded(string command)
{
    return currentGameState == WIN && command == CommandStrings::quit;
}

/**
 * Parses a command string to its numeric/enum representation and changes the game state based both the numeric and string
 * value of the user input.
 *
 * @param command The input command
 * @returns Whether or not a state change has taken place. If a change has not occured, it is because the state change
 * was not a valid one.
 */
bool GameEngine::changeStateFromCommand(Command *command)
{
    string commandString = command->getCommand();

    if (commandString == CommandStrings::quit)
    {
        return false;
    }

    if (commandString.find("loadmap") != std::string::npos)
    {
        command->saveEffect("Successfully loaded map file. State changed to MAPLOADED ");
        this->currentGameState = MAPLOADED;
        notify(this);
    }
    else if (commandString == CommandStrings::validateMap)
    {
        command->saveEffect("Map was successfully validated. State changed to MAPVALIDATED ");
        this->currentGameState = MAPVALIDATED;
        notify(this);
    }
    else if (commandString.find("addplayer") != std::string::npos)
    {
        command->saveEffect("Player  was added successfully ");
        this->currentGameState = PLAYERSADDED;
        notify(this);
    }
    else if (commandString == CommandStrings::gameStart)
    {
        command->saveEffect("Map added and validated successfully. All players added. Transitioned from start up phase into main game loop! ");
        this->currentGameState = ASSIGNREINFORCEMENTS;
        notify(this);
    }
    else if (commandString == CommandStrings::replay)
    {
        command->saveEffect("Restarting game");
        this->currentGameState = START;
        notify(this);
    }
    else
    {
        cout << "Error: command string is invalid after being checked for validity!" << endl;
        return false;
    }

    notify(this);

    return true;
}

/**
 * Checks if the current game state is "Win".
 *
 * @returns Whether or not a player has won
 */
bool GameEngine::hasPlayerWon()
{
    return currentGameState == WIN;
}

/**
 * Command-based user interaction mechanism to start the game
 */
void GameEngine::startupPhase()
{
    bool inStartup = true;

    while (inStartup)
    {
        Command *nextCommand = commandProcessor->getCommand();

        vector<Command *> commands = commandProcessor->getCommandsList();

        if (commandProcessor->validate(nextCommand, currentGameState))
        {
            inStartup = processCommand(nextCommand);
        }

        cout << nextCommand->getEffect() << endl;
    }
}

/**
 * Processes a Command object and performs any necessary actions and state changes necessary.
 * Assumes the command has already been validated.
 *
 * @param command The command to process
 * @return If the startup phase should continue
 */
bool GameEngine::processCommand(Command *command)
{
    string commandString = commandProcessor->splitStringByDelim(command->getCommand(), ' ').front();

    if (commandString == CommandStrings::loadMap)
    {
        loadMap(command);
    }
    else if (commandString == CommandStrings::validateMap)
    {
        validateMap(command);
    }
    else if (commandString == CommandStrings::addPlayer)
    {
        if (playerList.size() == 6) {
            command->saveEffect("Maximum 6 players allowed in a game of Warzone");
        } else {
            addPlayer(command);
        }        
    }
    else if (command->getCommand() == CommandStrings::gameStart)
    {
        if (playerList.size() >= 2) {
            gameStart(command);
            return false;
        } else {
            command->saveEffect("Warzone games must be played with 2-6 players. Add more before starting.");
        }        
    }

    return true;
}

/**
 * Loads a map file into the worldMap object
 *
 * @param command The command to save the effect of loading the map into
 */
void GameEngine::loadMap(Command *command)
{
    MapLoader mapLoader;
    string mapName = commandProcessor->splitStringByDelim(command->getCommand(), ' ').back();

    worldMap = mapLoader.LoadMap(mapName);

    if (worldMap == nullptr) {
        command->saveEffect("Map " + mapName + " does not exist. State has not been changed");
    } else {
        command->saveEffect("Successfully loaded map file " + mapName + ". State changed to MAPLOADED ");        
        setGameState(MAPLOADED);
    }    
}

/**
 * Validates loaded world map file.
 *
 * @param command The command to save the effect of validating the map into
 */
void GameEngine::validateMap(Command *command)
{
    if (worldMap->validate())
    {
        setGameState(MAPVALIDATED);
        cout << "Here is the game map:" << endl;
        cout << *worldMap << endl;
        command->saveEffect("Map was successfully validated. State changed to MAPVALIDATED ");
    }
    else
    {
        command->saveEffect("MAP was not a valid map. No state changes occured");
    }
}

void GameEngine::addPlayer(Command *command) {
    int playerNumber = playerList.size();
    if (playerNumber <= 6){
        string playerName = commandProcessor->splitStringByDelim(command->getCommand(), ' ').back();
        Player* player = new Player();
        Hand* tempHand = new Hand(player);
        player->setHand(tempHand);
        player->setName(playerName);
        playerList.push_back(player);
        setGameState(PLAYERSADDED);
        command->saveEffect("Player " + playerName + " was added successfully ");
    } else {
        command->saveEffect("Player number reaches the maximum. No more players can be added!");
        return;
    }
    
}

void GameEngine::gameStart(Command *command) {
    int playerNumber = playerList.size();
    if(playerNumber < 2){
        command->saveEffect("At least two players are needed to start the game! Failure: ");
    } else {
        
        for (int i = 0; i < 50; i++) {
            x->addCardToDeck(new Card());
        }

        assignPlayersOrder(&playerList);
        // distributeTerritories();
        for (Player* i : playerList) {
            i->setReinforcementPool(50);
            x->draw(i->getHand());
            x->draw(i->getHand());
        }

        setGameState(ASSIGNREINFORCEMENTS);
        command->saveEffect("Map added and validated successfully. All players added. Transitioned from start up phase into main game loop! ");
    }
}

void GameEngine::assignPlayersOrder(vector<Player*>* playerList)
{   
    cout << "Original player list: " << endl;
    for(auto& player : *playerList){
        cout << player->getName() << endl;
    }
    //std::random_shuffle(playerList->begin(),playerList->end());
    cout << "Randomize player order: " << endl;
    for(auto& player : *playerList){
        cout << player->getName() << endl;
    }
}

void GameEngine::distributeTerritories(Map* worldMap, vector<Player*>* playerList)
{
    for(auto& kv : worldMap->nodes){
        for(auto& player : *playerList){
            
        }
    }
}

/**
 * Sets current game state based on input new state.
 *
 * @param newGameState What to change the current game state to
 */
void GameEngine::setGameState(GameStates newGameState)
{
    currentGameState = newGameState;
    notify(this);
}


set<pair<Player*, Player*>> GameEngine::getAlliances()
{
    return alliances;
}

void GameEngine::setAlliances(set<pair<Player*, Player*>> alliances)
{
    this->alliances = alliances;
}

void GameEngine::addAlliance(Player* attacker, Player* attackee)
{
    alliances.insert(make_pair(attacker, attackee));
}

void GameEngine::emptyAlliances()
{
    for(auto it : alliances)
    {
        it.first = nullptr;
        it.second = nullptr;
    }
    alliances.clear();
}

bool GameEngine::isAllied(Player* attacker, Player* attackee)
{
    for(auto it : alliances)
    {
        if(it.first == attacker && it.second == attackee)
        {
            return true;
        }
    }
    return false;
}

/**
 * gamestart command triggers state change to ASSIGNREINFORCEMENT and call mainGameLoop
 * Loop between reinforcement, issuing orders, and execute orders.
 */
void GameEngine::mainGameLoop()
{
    cout << "****Main game loop Starting****" <<endl <<endl;
    //********For Assignement 2 only**********
    currentGameState = ASSIGNREINFORCEMENTS;
    //****************************************
    while (currentGameState != WIN)
    {
        cout << "We are on turn " << turnNumber << endl << "Type anything to proceed" <<endl;

        vector<Player*> currentPlayers = this->playerList;

        for(Player* current : currentPlayers){
            if(current->getTerritories().size()){
                vector<Player*>::iterator playerIt = find(currentPlayers.begin(), currentPlayers.end(), current);
                if(playerIt != currentPlayers.end()){
                    cout << "Player " << current->getName() << " has been eliminated" << endl;
                    currentPlayers.erase(playerIt);
                    this->deadPlayers.push_back(current);
                    this->playerList = currentPlayers;
                }
            }
        }

        string temp;
        cin >> temp;

        if(this->playerList.size() == 1){
            cout << "Player " << playerList.at(0)->getName() << " has won the game " << endl;
            currentGameState = WIN;
            continue;
        }

        if(turnNumber == 10){
            currentGameState = WIN;
            continue;
        }

        if (currentGameState == ASSIGNREINFORCEMENTS)
        {
            reinforcementPhase();
        }
        else if (currentGameState == ISSUEORDERS)
        {
            issueOrdersPhase();
        }
        else
        {
            executeOrdersPhase();
        }

        turnNumber++;
    }

    cout << "Main game ended" << endl;
}

/**
 * calculate and assign armies to each player
*/
void GameEngine::reinforcementPhase() {

    cout << "Reinforcement Phase for turn " << turnNumber << endl;
    for (Player* i : playerList) {

        int pool = i->getTerritories().size();
        
        int continent_bonus = i->getContinentsBonus();
        int total_bonus = ((pool / 3) > 3)? (pool / 3) : 3;
        total_bonus += continent_bonus;

        cout << "Reinforcing player " << i->getName() << " with " << total_bonus << " troops" << endl << "Type anything to continue ";
        
        string temp;
        cin >> temp; 

        i->setReinforcementPool(total_bonus);
    }
    currentGameState = ISSUEORDERS;
    notify(this);
}

void GameEngine::issueOrdersPhase() {

    int currentPlayers = playerList.size();

    string temporary;

    finishedPlayers = 0;

    for(Player* player : playerList){
        player->setTurn(false);
        player->numAttacks = 0;
        player->numDefense = 0;
    }

    cout << "Issue Order Phase for turn " << turnNumber << endl << "There are currently " << playerList.size() << " players in the game" << endl << "Type anything to continue:";
    cin >> temporary;

    while (finishedPlayers != currentPlayers) {

        cout << "Round Robin. There are " << finishedPlayers << " who have ended their turn" << endl;

        for (Player * temp: playerList)
        {
            if (temp->getTurn()) {
                continue; //Player has ended turn so we done
            }

            cout << "Order for player " << temp->getName() << endl;

            if (temp->getOrdersList().order_list.size() > 5) {
                if (!temp->getHand()->getHand().empty()) {
                    vector<Card*> cards = temp->getHand()->getHand();
                    cards[0]->play(temp->getHand());
                }
                temp->setTurn(true);
                finishedPlayers++;
                cout << "Player " << temp->getName() << " has ended their turn" << endl;

            } else{
                temp->issueOrder();
            }

            cout << "Type anything to continue: ";
            cin >> temporary;
        }
    }

    currentGameState = EXECUTEORDERS;
    notify(this);
}

void GameEngine::executeOrdersPhase()
{
    cout << "Execute Order Phase";
    for (Player* i : playerList) {
        for (Order* p : i->getOrdersList().order_list) {
            p->execute();
        }
    }

    currentGameState = ASSIGNREINFORCEMENTS;
    notify(this);
}

/**
 * Starts a new instance of Warzone
*/
void GameEngine::startNewGame() {
    displayWelcomeMessage();

    startupPhase();

    mainGameLoop();
}

//Return game state
string GameEngine::stringToLog()
{
    return "New game state is: " + getGameStateAsString() + "\n";
}

//Getter and Setter for playerList
vector<Player*> GameEngine::getPlayerList()
{
    return playerList;
}

void GameEngine::setPlayerList(vector<Player*> playerList)
{
    this->playerList = playerList;
}

vector<Player*> GameEngine::getDeadPlayers()
{
    return deadPlayers;
}

void GameEngine::setDeadPlayer(vector<Player*> deadPlayers)
{
    this->deadPlayers = deadPlayers;
}