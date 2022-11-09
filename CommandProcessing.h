#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using std::string;
using std::ostream;
using std::vector;

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

class Command {
public:
    Command();
    Command(string commandString);
    ~Command();

    void saveEffect(string effectString);
    string getEffect();

    string getCommand();
private:
    string command;
    string effect;
};

class FileProcessor {
public:
    FileProcessor();
    vector<string> processCommands(string filePath);
    ~FileProcessor();
};

class CommandProcessor {
public:
    CommandProcessor();
    static bool validate(Command* command, GameStates currentGameState);
    void getCommand();
    vector<Command*> getCommandsList();
    virtual ~CommandProcessor();
protected:
    vector<Command*> commandsList;
    virtual string readCommand();
    void saveCommand(string command);
};

bool validateCommandString(Command* command);

class FileCommandProcessorAdapter : public CommandProcessor {
public:
    FileCommandProcessorAdapter();
    FileCommandProcessorAdapter(FileProcessor* file);
    ~FileCommandProcessorAdapter();
private:
    FileProcessor* fileReader;
    string readCommand();
};

/**
 * Struct that contains all definitions for command strings a user may input in a game of Warzone.
 *
 * As per go-ahead from prof, does not contain a definition for a copy constrctor or assignment operator since the
 * strings are static and are always going to be the same.
*/
struct CommandStrings {
    static const string loadMap;
    static const string validateMap;
    static const string addPlayer;
    static const string gameStart;
    static const string replay;
    static const string quit;

    static bool isStringCommandString(string input);

    friend ostream& operator << (ostream&, const CommandStrings&);
};