#include "GameEngine.h"

GameEngine::GameEngine() {
    this->currentGameState = nullptr;
}

GameEngine::GameEngine(std::string startingState) : currentGameState(&startingState) {
}

GameEngine::~GameEngine() {
    delete this->currentGameState;
}

string* GameEngine::getCurrentGameState() {
    return this->currentGameState;
}

/**
 * Copy constructor
 * */
GameEngine::GameEngine(const GameEngine &copy) {
    this->currentGameState = copy.currentGameState;
}

/*
 * Stream insertion operator
 * */
ostream& operator << (ostream &out, const GameEngine &engine) {
    out << "Current Game State: " << *engine.currentGameState << endl;
    return out;
}