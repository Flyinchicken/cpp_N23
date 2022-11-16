#pragma once

#include "CommandProcessing.h"
#include "Player.h"
#include "Card.h"
#include <algorithm>
#include <string>
#include <ostream>
#include <vector>

using std::ostream;
using std::string;

class Deck;
class Command;
class Map;
class CommandProcessor;

/**
 * Represents the principle game engine of Warzone that allows a user to start a new game with a console-driven
 * inteface.
 *
 * Controls the state of the game along with what commands and actions are allowed at each phase.
 */
class GameEngine : public Subject, public ILoggable
{
private:
    GameStates currentGameState; // Not a pointer type as per prof. Paquet's permission

    CommandProcessor* commandProcessor;

    vector<Player*> playerList;
    vector<Player*> deadPlayers;
    void displayPlayerList();

    void displayWelcomeMessage();
    void displayVictoryMessage();

    bool hasGameBeenEnded(string command);
    bool hasPlayerWon();

    //bool processCommand(Command* command);
    void loadMap(Command* command);
    void validateMap(Command* command);
    void addPlayer(Command* command);
    void gameStart(Command* command);
    void assignPlayersOrder(vector<Player*>* playerList);
    void distributeTerritories();

    void displayMapTerritories();

    // Alliances pair of players created by card negotiate in current turn
    // Empty it at the end of the turn

    set<pair<Player*, Player*>> alliances;

    string getGameStateAsString() const;
    friend ostream& operator<<(ostream&, const GameEngine&);



public:
    GameEngine();
    ~GameEngine();
    GameEngine(const GameEngine&);

    GameEngine& operator=(const GameEngine& engine);
    bool changeStateFromCommand(Command* command);

    // friend ostream& operator << (ostream&, const GameEngine&);

    void startNewGame();
    bool processCommand(Command* command);
    void startupPhase();
    void mainGameLoop();
    void reinforcementPhase();
    void issueOrdersPhase();
    void executeOrdersPhase();

    GameStates getCurrentGameState();
    void setGameState(GameStates newState);
    void displayCurrentGameState();

    void displayFarewellMessage();

    string stringToLog();

    // Getter for alliances
    set<pair<Player*, Player*>> getAlliances();
    // Empty alliances
    void emptyAlliances();

    // Setter for alliances
    void setAlliances(set<pair<Player*, Player*>> alliances);
    // Add a pair of players to alliances
    void addAlliance(Player* player1, Player* player2);
    // Determine two players are allies or not
    bool isAllied(Player* player1, Player* player2);

    // Getter and Setter for playerList only used in test driver
    void setPlayerList(vector<Player*> playerList);
    vector<Player*> getPlayerList();

    void setDeadPlayer(vector<Player*> deadPlayers);
    vector<Player*> getDeadPlayers();

    void reinforcementPhaseForLogObserverDriver();
};

extern GameEngine* ge;
extern Map* worldMap;
extern Deck* x;