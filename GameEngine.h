#pragma once

#include "CommandProcessing.h"
#include "Map.h"

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

        Map *worldMap;
        
        void displayWelcomeMessage();
        void displayFarewellMessage();
        void displayVictoryMessage();
        void displayCurrentGameState();

        string getUserInput();

        bool hasGameBeenEnded(string command);
        bool hasPlayerWon();

        void processCommand(Command *command);
        void loadMap(Command *command);
        void validateMap(Command *command);

        //bool changeStateFromCommand(string commandString);
        // this one can be removed
        bool setGameStateIfValid(GameStates newState, string commandString);

        string getGameStateAsString() const;
        friend ostream& operator<<(ostream&, const GameEngine&);

    public:
        GameEngine();
        ~GameEngine();
        GameEngine(const GameEngine&);

        GameEngine &operator = (const GameEngine &engine);
        bool changeStateFromCommand(string commandString);

       // friend ostream& operator << (ostream&, const GameEngine&);

        void startNewGame();

        void startupPhase();
        GameStates getCurrentGameState();
        void setGameState(GameStates newState);
};