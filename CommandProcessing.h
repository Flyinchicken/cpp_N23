#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Player.h"
#include "LoggingObserver.h"

using std::string;
using std::ostream;
using std::vector;

extern string filePath;

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

class Command : public Subject, public ILoggable {
public:
    Command();
    Command(string commandString);
    Command(const Command&);
    ~Command();

    void saveEffect(string effectString);
    string getEffect();

    string getCommand();

    friend ostream& operator << (ostream&, const Command&);
    Command& operator = (const Command&);

    string stringToLog();
private:
    string command;
    string effect;
};

class FileLineReader {
public:
    FileLineReader();
    FileLineReader(const FileLineReader&);
    ~FileLineReader();
    vector<string> processCommands(string filePath);

    friend ostream& operator <<(ostream&, const FileLineReader&);
    FileLineReader& operator =(const FileLineReader&);
};

class CommandProcessor : public Subject, public ILoggable {
public:
    CommandProcessor();
    CommandProcessor(const CommandProcessor&);
    virtual ~CommandProcessor();

    bool validate(Command* command, GameStates currentGameState);
    void getCommand();
    vector<Command*> getCommandsList();

    vector<string> splitStringByDelim(string toSplit, char delim);

    friend ostream& operator <<(ostream&, const CommandProcessor&);
    CommandProcessor& operator =(const CommandProcessor&);

    string stringToLog();
protected:
    vector<Command*> commandsList;
    virtual void readCommand();
    void saveCommand(string command);
    string savedCommand;
};

class FileCommandProcessorAdapter : public CommandProcessor {
public:
    FileCommandProcessorAdapter();
    FileCommandProcessorAdapter(FileLineReader* file);
    FileCommandProcessorAdapter(const FileCommandProcessorAdapter&);
    ~FileCommandProcessorAdapter();

    friend ostream& operator <<(ostream&, const FileCommandProcessorAdapter&);
    FileCommandProcessorAdapter& operator =(const FileCommandProcessorAdapter&);
private:
    FileLineReader* fileReader;
    void readCommand();
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