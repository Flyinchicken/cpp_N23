#include "CommandProcessing.h"

#include <iostream>
#include <cctype>
#include <sstream>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::stringstream;

//
//  COMMAND STRINGS
//

// Define command string constants
const string CommandStrings::loadMap = "loadmap";
const string CommandStrings::validateMap = "validatemap";
const string CommandStrings::addPlayer = "addplayer";
const string CommandStrings::gameStart = "gamestart";
const string CommandStrings::replay = "replay";
const string CommandStrings::quit = "quit";

/**
 * Checks if input string matches any of the valid command strings.
 *
 * @param input The string to check
 * @returns Boolean indicating if input string is a valid command string or not
 */
bool CommandStrings::isStringCommandString(string input)
{
    return input == loadMap || input == validateMap || input == addPlayer || input == gameStart || input == replay || input == quit;
}

/**
 * Stream insertion operator for CommandStrings. Will display current dictionary of command strings.
 */
ostream &operator<<(ostream &out, const CommandStrings &strings)
{
    out << "Current list of command strings: " << endl;

    // Done manually since could not find way to programmatically do it within C++ without the aid
    // of external libraries
    out << "1: "
        << "loadmap <filename>" << endl;
    out << "2: " << strings.validateMap << endl;
    out << "3: "
        << "addplayer <playername>" << endl;
    out << "4: " << strings.gameStart << endl;
    out << "5: " << strings.replay << endl;
    out << "6: " << strings.quit << endl;

    return out;
}

//
//  COMMAND
//

Command::Command()
{
    this->command = "";
    this->effect = "";
}

Command::Command(string commandString)
{
    this->command = commandString;
    this->effect = "";
}

Command::~Command()
{
    // Nothing to delete...for now
}

string Command::getCommand()
{
    return this->command;
}

void Command::saveEffect(string effectString)
{
    this->effect = effectString;
}

string Command::getEffect()
{
    return this->effect;
}

//
//  COMMAND PROCESSOR
//

CommandProcessor::CommandProcessor()
{
    this->commandsList = vector<Command *>();
}

bool has_suffix(const std::string &str, const std::string &suffix)
{
    return str.size() >= suffix.size() &&
           str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

// Check if the valid command can be used in the current game state
bool CommandProcessor::validate(Command *command, GameStates currentGameState)
{
    stringstream commandStream(command->getCommand());
    vector<string> segmentList;
    string commandSegment;

    while (getline(commandStream, commandSegment, ' '))
    {
        segmentList.push_back(commandSegment);
    }

    // There can only be two params
    if (segmentList.size() > 2)
    {
        command->saveEffect(command->getCommand() + " has too many parameters");
        cout << command->getCommand() + " has too many parameters " << endl;

        return false;
    }

    string commandString = segmentList.front();

    // Check to make sure 1st param is a valid command
    if (!CommandStrings::isStringCommandString(commandString))
    {
        command->saveEffect(commandString + " is not a valid command string");
        cout << "Invalid command." << endl;
        return false;
    }

    // Check to make sure has correct params
    if ((commandString == CommandStrings::loadMap || commandString == CommandStrings::addPlayer) && segmentList.size() != 2)
    {
        command->saveEffect(commandString + " must have only one valid parameter, separated by a white space");
        cout << commandString + " must have only one valid parameter, separated by a white space" << endl;

        return false;
    }
    if (commandString != CommandStrings::loadMap && commandString != CommandStrings::addPlayer && segmentList.size() != 1)
    {
        command->saveEffect(commandString + " cannot have any parameters");
        cout << commandString + " cannot have any parameters" << endl;

        return false;
    }

    // Check is valid in gamestate
    switch (currentGameState)
    {
    case START:
        if (commandString == CommandStrings::loadMap)
        {
            return true;
        }
        break;
    case MAPLOADED:
        if (commandString == CommandStrings::loadMap || commandString == CommandStrings::validateMap)
        {
            return true;
        }
        break;
    case MAPVALIDATED:
        if (commandString == CommandStrings::addPlayer)
        {
            return true;
        }
        break;
    case PLAYERSADDED:
        if (commandString == CommandStrings::addPlayer || commandString == CommandStrings::gameStart)
        {
            return true;
        }
        break;
    case WIN:
        if (commandString == CommandStrings::replay || commandString == CommandStrings::quit)
        {
            return true;
        }
        break;
    }

    command->saveEffect(command->getCommand() + " is not valid in the current game state");

    return false;
}

/**
 * Splits a string by a char delimeter.
 *
 * @param toSplit The string to split into pieces
 * @param delim The char delimeter - where to split the string
 * @returns A vector<string> of all the pieces of the string
 */
vector<string> CommandProcessor::splitStringByDelim(string toSplit, char delim)
{
    stringstream commandStream(toSplit);
    vector<string> segmentList;
    string segment;

    while (getline(commandStream, segment, delim))
    {
        segmentList.push_back(segment);
    }

    return segmentList;
}

void CommandProcessor::readCommand()
{
    while (true)
    {
        cout << "Give a command: (Type 'end' when you wish to stop) " << endl;
        string commandStr;
        getline(cin, commandStr);
        if (commandStr != "")
        {
            if (commandStr == "end")
            {
                return;
            }
            this->saveCommand(commandStr);
        }
    }
}

void CommandProcessor::saveCommand(string command)
{
    this->commandsList.push_back(new Command(command));
}

void CommandProcessor::getCommand()
{
    this->readCommand();
}

vector<Command *> CommandProcessor::getCommandsList()
{
    return this->commandsList;
}

CommandProcessor::~CommandProcessor()
{
}

/*
File Processor Adapter

*/

FileCommandProcessorAdapter::FileCommandProcessorAdapter()
{
    CommandProcessor();
    this->fileReader = new FileLineReader();
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(FileLineReader *file)
{
    CommandProcessor();
    this->fileReader = file;
}

FileCommandProcessorAdapter::~FileCommandProcessorAdapter()
{
}

void FileCommandProcessorAdapter::readCommand()
{

    // this->saveCommand("Opening file " + filePath);

    ifstream input(filePath);

    cout << filePath << endl;

    if (input.fail() && filePath != "")
    {
        cout << "Incorrect file path. Please provide a valid file when you execute the program." << endl;
        return;
    }

    vector<string> commands;
    commands = this->fileReader->processCommands(filePath);

    for (string i : commands)
        this->saveCommand(i);
}

/*
File Line Reader

*/

FileLineReader::FileLineReader()
{
}

FileLineReader::~FileLineReader()
{
}

vector<string> FileLineReader::processCommands(string filePath)
{

    vector<string> commands;
    string tempCommand;

    ifstream commandFile(filePath);

    while (getline(commandFile, tempCommand))
    {
        commands.push_back(tempCommand);
    }

    commandFile.close();
    return commands;
}