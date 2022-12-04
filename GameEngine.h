#pragma once

#include "CommandProcessing.h"
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
struct TournamentParams;

/**
 * Represents the principle game engine of Warzone that allows a user to start a new game with a console-driven
 * inteface.
 *
 * Controls the state of the game along with what commands and actions are allowed at each phase.
 */
class GameEngine : public Subject, public ILoggable
{
    friend ostream& operator<<(ostream&, const GameEngine&);
    private:
        GameStates currentGameState; // Not a pointer type as per prof. Paquet's permission

        CommandProcessor* commandProcessor;

        bool isTournament;
        TournamentParams* tournamentParams;
        // 2D vector of winners. 1st dimension is map$, second is game$
        vector<vector<string>> tournamentWinners;
        int tournamentGameNumber;
        int tournamentMapNumber;

        vector<Player*> playerList;
        vector<Player*> deadPlayers;
        void displayPlayerList();

        void displayWelcomeMessage();
        void displayVictoryMessage();

        bool hasGameBeenEnded(string command);
        bool hasPlayerWon();

        void validateMap(Command* command);
        void assignPlayersOrder(vector<Player*>* playerList);
        void distributeTerritories();

        void displayMapTerritories();

        // Alliances pair of players created by card negotiate in current turn
        // Empty it at the end of the turn

        set<pair<Player*, Player*>> alliances;

        string getGameStateAsString() const;

    public:
        GameEngine();
        ~GameEngine();
        GameEngine(const GameEngine&);

        GameEngine& operator=(const GameEngine& engine);
        bool changeStateFromCommand(Command* command);

        void startNewGame();
        bool processCommand(Command* command);
        void startupPhase();
        void mainGameLoop();
        void reinforcementPhase();
        void issueOrdersPhase();
        void executeOrdersPhase();

        /*
            Tournament methods:
                loadMap - Need to load maps into vector
                validatemaps - validate all maps in vector
                addPlayer - Can probably be mostly the same
                gamestart - Can be mostly the same
                mainGameLoop - Copy that doesn't have any user interaction & can have set # of turns. If +1 alive player at end = draw.
                outputResultsToFile - Output results of tournament to a file
        */
       void tournamentSetup(Command*);
       void tournamentGameLoop();
       bool loadTournamentMap(string);
       void addTournamentPlayers();
       void outputTournamentResults();

        GameStates getCurrentGameState();
        void setGameState(GameStates newState);
        void displayCurrentGameState();
        
        // Public for testing
        void loadMap(Command* command);
        void addPlayer(Command* command);
        void gameStart(Command* command);

        Player* getPlayerIfExists(string);

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
extern bool realGame;       // Indicating if game instance is real or a test