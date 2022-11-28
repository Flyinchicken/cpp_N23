#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "LoggingObserver.h"

using std::ostream;
using std::string;
using std::vector;

extern string filePath;

/**
 * Represents the possible states of a Warzone game.
 */
enum GameStates
{
    START,
    MAPLOADED,
    MAPVALIDATED,
    PLAYERSADDED,
    ASSIGNREINFORCEMENTS,
    ISSUEORDERS,
    EXECUTEORDERS,
    WIN
};

class Command : public Subject, public ILoggable
{
public:
    Command();
    Command(string commandString);
    Command(const Command &);
    ~Command();

    void saveEffect(string effectString);
    string getEffect();

    string getCommand();

    friend ostream &operator<<(ostream &, const Command &);
    Command &operator=(const Command &);

    string stringToLog();

private:
    string command;
    string effect;
};

class FileLineReader
{
public:
    FileLineReader();
    FileLineReader(const FileLineReader &);
    ~FileLineReader();

    string readLineFromFile();

    friend ostream &operator<<(ostream &, const FileLineReader &);
    FileLineReader &operator=(const FileLineReader &);

private:
    ifstream fileInputStream;
};

class CommandProcessor : public Subject, public ILoggable
{
public:
    CommandProcessor();
    CommandProcessor(const CommandProcessor &);
    virtual ~CommandProcessor();

    bool validate(Command *command, GameStates currentGameState);
    Command *getCommand();
    vector<Command *> getCommandsList();

    vector<string> splitStringByDelim(string toSplit, char delim);

    friend ostream &operator<<(ostream &, const CommandProcessor &);
    CommandProcessor &operator=(const CommandProcessor &);

    string stringToLog();

protected:
    vector<Command *> commandsList;
    string savedCommand;

    virtual string readCommand();
    void saveCommand(string command);
};

class FileCommandProcessorAdapter : public CommandProcessor
{
public:
    FileCommandProcessorAdapter();
    FileCommandProcessorAdapter(FileLineReader *file);
    FileCommandProcessorAdapter(const FileCommandProcessorAdapter &);
    ~FileCommandProcessorAdapter();

    friend ostream &operator<<(ostream &, const FileCommandProcessorAdapter &);
    FileCommandProcessorAdapter &operator=(const FileCommandProcessorAdapter &);

private:
    FileLineReader *fileReader;
    string readCommand();
};

/**
 * Struct that contains all definitions for command strings a user may input in a game of Warzone.
 *
 * As per go-ahead from prof, does not contain a definition for a copy constrctor or assignment operator since the
 * strings are static and are always going to be the same.
 */
struct CommandStrings
{
    static const string loadMap;
    static const string validateMap;
    static const string addPlayer;
    static const string gameStart;
    static const string replay;
    static const string quit;
    static const string issueOrder;
    static const string issueOrdersEnd;

    static bool isStringCommandString(string input);

    friend ostream &operator<<(ostream &, const CommandStrings &);
};