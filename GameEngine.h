#pragma once

#include <string>
#include <ostream>

using namespace std;

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
        int *currentGameState;                                      // What state the game is in currently

        bool isValidStateTransition(int newGameState);              // Determines if can move from one to another

        friend ostream& operator <<(ostream&, const GameEngine&);   // Assignment insertion operator

    public:
        GameEngine();                                       // Default constructor
        ~GameEngine();                                      // Destructor
        GameEngine(const GameEngine&);                      // Copy constructor
        GameEngine &operator=(const GameEngine &engine);    // Assignment operator

        int getCurrentGameState();
        int setCurrentGameState(int newGameState);
        // Would need constant string array/dictionary of valid command strings to compare against
        // If valid, try to set current
        // If not valid, complain
        void processCommandString(string commandString);
};