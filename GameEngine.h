#pragma once

#include <string>
#include <vector>
#include <ostream>

using namespace std;

/**
 * Represents the principle game engine of Warzone that allows a user to start a new game with a console-driven
 * inteface.
 * 
 * Controls the state of the game along with what commands and actions are allowed at each phase.
*/
class GameEngine {
    private:
        /**
         * Represents the possible states of a Warzone game.
        */
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

        friend ostream& operator <<(ostream&, const GameEngine&);

        void displayWelcomeMessage();
        void displayFarewellMessage();
        void displayVictoryMessage();
        void displayCurrentGameState();

        string getUserInput();

        bool isValidCommandString(string commandString);
        bool hasGameBeenEnded(string commandString);
        bool hasPlayerWon();

        bool changeStateFromCommand(string commandString);
        bool setGameStateIfValid(GameStates newState, string commandString);

        string getGameStateAsString() const;

    public:
        GameEngine();
        ~GameEngine();
        GameEngine(const GameEngine&);
        GameEngine &operator=(const GameEngine &engine);

        void startNewGame();
};