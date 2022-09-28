#ifndef GAMEENGINE_H
#define GAMEENGINE_H

using namespace std;
#include <string>
#include <ostream>

class GameEngine {
    private:
        string *currentGameState;
        friend ostream& operator <<(ostream&, const GameEngine&);
    public:
        GameEngine();
        GameEngine(string startingState);
        ~GameEngine();
        GameEngine(const GameEngine&);

        string* getCurrentGameState();
};

#endif