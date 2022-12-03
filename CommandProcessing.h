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

/**
 * Struct containing all information acquired from a tournament console command
*/
struct TournamentParams {
    vector<string> maps;  // Make worldMap = current playing map
    vector<string> players;
    int numGames;
    int numTurns;

    TournamentParams();
    TournamentParams(const TournamentParams&);
    TournamentParams& operator = (const TournamentParams&);
    ~TournamentParams();

    friend ostream& operator << (ostream&, TournamentParams&);
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
    bool validateTournamentCommand(vector<string>, Command*);
    TournamentParams processTournamentCommand(Command*);
    /*
        Validate tournament command
            Is command string = tournament
            Are there 1-5 commands after -M
            Are there 2-4 commands after -P
            Is number after -G between 1 and 5
            Is number after -D between 10 and 50
        Process tournament command
            Use global GameEngine
            Assume has already been validated
            Call appropriate *ge commands to get it started
    */

protected:
    vector<Command *> commandsList;
    string savedCommand;

    virtual string readCommand();
    void saveCommand(string command);
    bool isStringNumber(string);
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
    static const string tournament;

    static bool isStringCommandString(string input);

    friend ostream &operator<<(ostream &, const CommandStrings &);
};