#pragma once

#include <string>
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

        GameStates currentGameState;                // Not a pointer type as per prof. Paquet

        void displayWelcomeMessage();
        void displayFarewellMessage();
        void displayVictoryMessage();
        void displayCurrentGameState();

        string getUserInput();

        bool hasGameBeenEnded(string commandString);
        bool hasPlayerWon();

        bool changeStateFromCommand(string commandString);
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

/**
 * Struct that contains all definitions for command strings a user may input in a game of Warzone.
*/
struct CommandStrings {
    static const string loadMap;
    static const string validateMap;
    static const string addPlayer;
    static const string assignCountries;
    static const string issueOrder;
    static const string endIssueOrders;
    static const string execOrder;
    static const string endExecOrders;
    static const string win;
    static const string play;
    static const string end;

    static bool isStringCommandString(string input);
};