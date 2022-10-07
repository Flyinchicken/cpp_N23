#pragma once

#include <string>
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
        int currentGameState;                                       // What state the game is in currently 
        bool gameInProgress;                                        // If a game has been started and is in progress

        bool isValidStateTransition(int newGameState) const;              // Determines if can move from one to another
        bool isValidCommandString(string commandString) const;            // Determines if a command string is a valid one

        friend ostream& operator <<(ostream&, const GameEngine&);   // Assignment insertion operator

    public:
        GameEngine();                                       // Default constructor
        ~GameEngine();                                      // Destructor
        GameEngine(const GameEngine&);                      // Copy constructor
        GameEngine &operator=(const GameEngine &engine);    // Assignment operator

        int getCurrentGameState() const;
        void setCurrentGameState(int newGameState);
        string getGameStateAsString() const;                              // Returns the current game state as a string

        void processCommandString(string commandString);

        bool isGameInProgress() const;   
        void setGameInProgress(bool gameInProgress);         
};