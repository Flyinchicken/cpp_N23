#pragma once

#include <string>
#include <vector>
#include <ostream>

using namespace std;

/**
 * TODO: Figure out how make static/constant arrays for valid game states and command strings 
 * TODO: Where cin/main game loop go?
 * */




/**
 * State = certain phase of game
 *          What are valid actions and user commands take place
 *          Some action may trigger transition to another state
 * 
 * States = 
 *      Start, Map loaded, Map validated, Players added, Assign reinforcement, issue orders, execute orders, win
 * Command strings =
 *      loadmap, validatemap, addplayer, assigncounties, issueorder, endissueorders, execorder, endexecorders, win, play, end
 * */
class GameEngine {
    private:
        enum GameStates {
            START,
            MAPLOADED,
            MAPVALIDATED,
            PLAYERSADDED,
            ASSIGNREINFORCEMENTS,
            ISSUEORDERS,
            EXECUTEORDERS,
            WIN
        };

        GameStates currentGameState;
        vector<string> validCommandStrings;

        friend ostream& operator <<(ostream&, const GameEngine&);   // Assignment insertion operator

        void displayWelcomeMessage();
        void displayFarewellMessage();
        void displayVictoryMessag();
        void displayCurrentGameState();

        string getUserInput();

        bool isValidCommandString(string commandString);
        bool hasGameBeenEnded(string commandString);
        bool hasPlayerWon();

        bool changeStateFromCommand(string commandString);
        bool setGameStateIfValid(GameStates newState, string commandString);

        string getGameStateAsString() const;                              // Returns the current game state as a string

    public:
        GameEngine();                                       // Default constructor
        ~GameEngine();                                      // Destructor
        GameEngine(const GameEngine&);                      // Copy constructor
        GameEngine &operator=(const GameEngine &engine);    // Assignment operator

        void startNewGame();
};