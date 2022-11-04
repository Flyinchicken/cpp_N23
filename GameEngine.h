#pragma once

#include "CommandProcessing.h"

#include <string>
#include <ostream>

using std::string;
using std::ostream;

/**
 * Represents the principle game engine of Warzone that allows a user to start a new game with a console-driven
 * inteface.
 * 
 * Controls the state of the game along with what commands and actions are allowed at each phase.
*/
class GameEngine {
    private:
        GameStates currentGameState;                // Not a pointer type as per prof. Paquet's permission

        CommandProcessor *commandProcessor;
        
        void displayWelcomeMessage();
        void displayFarewellMessage();
        void displayVictoryMessage();
        void displayCurrentGameState();

        string getUserInput();

        bool hasGameBeenEnded(string command);
        bool hasPlayerWon();

        bool changeStateFromCommand(string commandString);
        // this one can be removed
        bool setGameStateIfValid(GameStates newState, string commandString);

        string getGameStateAsString() const;

    public:
        GameEngine();
        ~GameEngine();
        GameEngine(const GameEngine&);

        GameEngine &operator = (const GameEngine &engine);
        friend ostream& operator << (ostream&, const GameEngine&);

        void startNewGame();
};