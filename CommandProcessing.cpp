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
ostream& operator<<(ostream& out, const CommandStrings& strings)
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

/**
 * Default constructor
*/
Command::Command()
{
    this->command = "";
    this->effect = "";
}

/**
 * Constructor that takes a and sets command string.
 *
 * @param commandString The command string to init Command with
*/
Command::Command(string commandString)
{
    this->command = commandString;
    this->effect = "";
}

/**
 * Copy constructor. Copies over effect and command of one to copy.
 *
 * @param copyCommand Command object to copy
*/
Command::Command(const Command& copyCommand) {
    this->command = copyCommand.command;
    this->effect = copyCommand.effect;
}

/**
 * Assignment operator. Sets command and effect.
*/
Command& Command::operator=(const Command& equalCommand) {
    this->command = equalCommand.command;
    this->effect = equalCommand.effect;

    return *this;
}

/**
 * Stream insertion operator. Displays Command string and effect string (if there is one)
*/
ostream& operator<<(ostream& out, const Command& streamCommand) {
    string effectString = streamCommand.effect.empty() ? "No current effect" : streamCommand.effect;

    out << "Command: " << streamCommand.command
        << "Effect: " << effectString
        << endl;

    return out;
}

/**
 * Destructor
*/
Command::~Command()
{
    // Nothing to delete...for now
}

/**
 * @returns command string of Command
*/
string Command::getCommand()
{
    return this->command;
}

/**
 * Sets the effect string based on input
 *
 * @param effectString String to set the effect with
*/
void Command::saveEffect(string effectString)
{
    this->effect = effectString;
    notify(this);
}

/**
 * @returns effect string of Command
*/
string Command::getEffect()
{
    return this->effect;
}

//Return the Command's effect
string Command::stringToLog()
{
    return this->effect + "\n";
}

//
//  COMMAND PROCESSOR
//

/**
 * Default constructor.
*/
CommandProcessor::CommandProcessor()
{
    this->commandsList = vector<Command*>();
}

/**
 * Copy Constructor.
*/
CommandProcessor::CommandProcessor(const CommandProcessor& processor) {
    this->commandsList = processor.commandsList;
}

/**
 * Destructor
*/
CommandProcessor::~CommandProcessor() {
    for (Command* command : commandsList) {
        delete command;
    }

    commandsList.clear();
}

/**
 * Assignment operator.
*/
CommandProcessor& CommandProcessor::operator=(const CommandProcessor& processor) {
    this->commandsList = processor.commandsList;

    return *this;
}

/**
 * Stream insertion operator. Prints command list
*/
ostream& operator<<(ostream& out, const CommandProcessor& processor) {
    for (Command* command : processor.commandsList) {
        out << command;
    }

    return out;
}

bool has_suffix(const std::string& str, const std::string& suffix)
{
    return str.size() >= suffix.size() &&
        str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

/**
 * Check command is valid in current game state.
 * Doesn't check if map in "loadmap <map>" is valid, as logic for validating a map file should handle that.
 * Saves effect rather than cout'ing as logic in most game loops involves printing the effect of a command.
 *
 * @param command The command to validate
 * @param currentGameState Current state of the game
 * @return If command is valid or not in the current state
 * */
bool CommandProcessor::validate(Command* command, GameStates currentGameState)
{
    if (command->getCommand().empty()) {
        command->saveEffect("Command strings cannot be empty!");

        return false;
    }

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

        return false;
    }

    string commandString = segmentList.front();

    // Check to make sure 1st param is a valid command
    if (!CommandStrings::isStringCommandString(commandString))
    {
        command->saveEffect(commandString + " is not a valid command string");

        return false;
    }

    // Check to make sure has correct params
    if ((commandString == CommandStrings::loadMap || commandString == CommandStrings::addPlayer) && segmentList.size() != 2)
    {
        command->saveEffect(commandString + " must have only one valid parameter, separated by a white space");

        return false;
    }
    if (commandString != CommandStrings::loadMap && commandString != CommandStrings::addPlayer && segmentList.size() != 1)
    {
        command->saveEffect(commandString + " cannot have any parameters");

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

/**
 * Gets a single command from the console.
 * 
 * @return The command input as a string
*/
string CommandProcessor::readCommand()
{
    cout << "Input your next command: " << endl;

    string commandString;
    getline(cin, commandString);

    return commandString;
}

/**
 * Saves a command string into the command list
*/
void CommandProcessor::saveCommand(string command)
{
    this->commandsList.push_back(new Command(command));

    this->savedCommand = command;

    notify(this);
}

/**
 * Reads and saves a Command taken from either the console or a file.
 * 
 * @returns Command object taken from input method
*/
Command* CommandProcessor::getCommand()
{
    string commandString = this->readCommand();

    this->saveCommand(commandString);

    return this->commandsList.back();
}

/**
 * @returns The entire command list
*/
vector<Command*> CommandProcessor::getCommandsList()
{
    return this->commandsList;
}

//Return the Command saved
string CommandProcessor::stringToLog()
{
    return "\n"+ this->savedCommand + "\n";
}

///
/// File Processor Adapter
///

/**
 * Default constructor.
*/
FileCommandProcessorAdapter::FileCommandProcessorAdapter()
{
    CommandProcessor();
    this->fileReader = new FileLineReader();
}

/**
 * Constructor that takes a FileLineReader.
 *
 * @param file FileLineReader to set current fileReade to
*/
FileCommandProcessorAdapter::FileCommandProcessorAdapter(FileLineReader* file)
{
    CommandProcessor();
    this->fileReader = file;
}

/**
 * Copy constructor. Sets fileReader to input's fileReader
 *
 * @param adapter FileCommandProcessorAdapter to copy
*/
FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter& adapter) {
    CommandProcessor();
    this->fileReader = adapter.fileReader;
}

/**
 * Destructor
*/
FileCommandProcessorAdapter::~FileCommandProcessorAdapter()
{
    delete this->fileReader;
}

/**
 * Assignment operator.
*/
FileCommandProcessorAdapter& FileCommandProcessorAdapter::operator=(const FileCommandProcessorAdapter& adapter) {
    this->fileReader = adapter.fileReader;

    return *this;
}

/**
 * Stream insertion operator. Prints command list
*/
ostream& operator<<(ostream& out, const FileCommandProcessorAdapter& adapter) {
    for (Command* command : adapter.commandsList) {
        out << command;
    }

    return out;
}

/**
 * Reads commands from the global file path
*/
string FileCommandProcessorAdapter::readCommand()
{
    string commandString = this->fileReader->readLineFromFile();

    cout << commandString << endl;

    return commandString;
}

///
/// File Line Reader
///

/** Default constructor */
FileLineReader::FileLineReader() {
    this->fileInputStream = ifstream(filePath);
}

/** Copy constructor */
FileLineReader::FileLineReader(const FileLineReader& reader) {
    // Nothing to copy
}

/** Destructor */
FileLineReader::~FileLineReader() {
    this->fileInputStream.close();
}

/** Stream insertion operator */
ostream &operator <<(ostream &out, const FileLineReader &reader) { return out; }

/** Assignment operator */
FileLineReader &FileLineReader::operator=(const FileLineReader &reader) { return *this; }

/**
 * Reads a single line from a command file
 * 
 * @returns Line from the command file as a string
*/
string FileLineReader::readLineFromFile() {
    if (fileInputStream.eof()) {
        return "fileEnd";
    }

    string fileLine;

    getline(fileInputStream, fileLine);

    return fileLine;
}