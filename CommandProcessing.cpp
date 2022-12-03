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
const string CommandStrings::issueOrder = "issueorder";
const string CommandStrings::issueOrdersEnd = "issueordersend";
const string CommandStrings::tournament = "tournament";

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

///
/// TOURNAMENT PARAMETERS
///

/**
 * Default constructor
*/
TournamentParams::TournamentParams() {
    maps = {};
    players = {};
    numGames = 0;
    numTurns = 0;
}

/**
 * Destructor.
*/
TournamentParams::~TournamentParams() {
    maps.clear();
    players.clear();
}

/**
 * Copy constructor
*/
TournamentParams::TournamentParams(const TournamentParams& toCopy) {
    maps = toCopy.maps;
    players = toCopy.players;
    numGames = toCopy.numGames;
    numTurns = toCopy.numTurns;
}

/**
 * Assignment operator
*/
TournamentParams& TournamentParams::operator=(const TournamentParams& toCopy) {
    if (&toCopy != this) {
        maps = toCopy.maps;
        players = toCopy.players;
        numGames = toCopy.numGames;
        numTurns = toCopy.numTurns;
    }

    return *this;
}

/**
 * Stream insertion operator
*/
ostream& operator << (ostream& out, TournamentParams& params) {
    out << "Maps: " << endl;
    for (string map : params.maps) {
        out << "\t" << map << endl;
    }

    out << "Players: " << endl;
    for (string player : params.players) {
        out << "\t" << player << endl;
    }

    out << "Number of turns per game: " << params.numTurns << endl;
    out << "Numer of total games: " << params.numGames << endl;

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
    return "Command's effect: " + this->effect + "\n";
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
 * Determines if a string is an int/number.
 * 
 * From: https://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
 * 
 * @returns bool indicating if string is a number
*/
bool CommandProcessor::isStringNumber(string input) {
    std::string::const_iterator iterator = input.begin();

    while (iterator != input.end() && isdigit(*iterator)) {
        ++iterator;
    }

    return !input.empty() && iterator == input.end();
}

/**
 * Iterates over tournament command and sets various parameters for a tournament. Assumes command has
 * already been validated.
 * 
 * @param command The tournament Command
 * @returns TournamentParams containing all information
*/
TournamentParams CommandProcessor::processTournamentCommand(Command* command) {
    vector<string> commandList = splitStringByDelim(command->getCommand(), ' ');

    int currentProcessing = 1;
    TournamentParams params;
    for (int i = 2; i < commandList.size(); i++) {
        if (commandList.at(i) == "-P") {
            currentProcessing = 2;
            continue;
        } else if (commandList.at(i) == "-G") {
            currentProcessing = 3;
            continue;
        } else if (commandList.at(i) == "-D") {
            currentProcessing = 4;
        }
        else {
            if (currentProcessing == 1) {
                params.maps.push_back(commandList.at(i));
            } else if (currentProcessing == 2) {
                params.players.push_back(commandList.at(i));
            } else if (currentProcessing == 3) {
                params.numGames = stoi(commandList.at(i));
            } else if (currentProcessing == 4) {
                params.numTurns = stoi(commandList.at(i));
            } 
        }        
    }

    return params;
}

/**
 * Validates that a tournament command string is valid
 * 
 * @param commandList The command broken up by whitespace
 * @param Command The command object the command came from. Used here to saveEffect
 * @returns If it is valid or not
*/
bool CommandProcessor::validateTournamentCommand(vector<string> commandList, Command* command) {
    // Min 10, max 16 commands in sequence
    if (commandList.size() < 10 || commandList.size() > 16) {
        command->saveEffect("Tournament command contains too few or too many parameters");
        return false;
    }

    if (commandList.at(1) != "-M") {
        command->saveEffect("Tournament command improperly formatted (map number must come first)");
        return false;
    }

    int maxMapCounter = 7;
    int mapCounter = 2;
    bool nextIsPlayer = false;
    // Min 1, max 5 maps
    while (mapCounter < maxMapCounter) {
        if (mapCounter == 2 && (commandList.at(mapCounter) == "-P" || commandList.at(mapCounter) == "-G" || commandList.at(mapCounter) == "-D" || commandList.at(mapCounter) == "-M")) {
            command->saveEffect("Tournament command contains no map files");
            return false;
        }
        else if (commandList.at(mapCounter) == "-G" || commandList.at(mapCounter) == "-D" || commandList.at(mapCounter) == "-M") {
            command->saveEffect("Tournament command improperly formatted (players must come after maps)");
            return false;
        }

        if (commandList.at(mapCounter) == "-P") {
            nextIsPlayer = true;
            break;
        }
        ++mapCounter;
    }  
    if (!nextIsPlayer && commandList.at(mapCounter) != "-P") {
        command->saveEffect("Tournament command contains too many map files or player count does not follow maps");
        return false;
    }

    // Into players, counter is now on first strat
    int playerCounter = mapCounter + 1;
    int maxPlayerCounter = playerCounter + 4;
    bool nextIsGameNumber = false;
    // Max 4 players
    while (playerCounter < maxPlayerCounter) {
        if ((playerCounter == mapCounter + 2) && (commandList.at(playerCounter) == "-P" || commandList.at(playerCounter) == "-G" || commandList.at(playerCounter) == "-D" || commandList.at(playerCounter) == "-M")) {
            command->saveEffect("Tournament command contains no players");
            return false;
        }
        else if (commandList.at(playerCounter) == "-P" || commandList.at(playerCounter) == "-D" || commandList.at(playerCounter) == "-M") {
            command->saveEffect("Tournament command improperly formatted (number of games must come after players)");
            return false;
        }

        if (commandList.at(playerCounter) == "-G") {
            nextIsGameNumber = true;
            break;
        }

        if (!nextIsGameNumber && commandList.at(playerCounter) != "Aggressive" && commandList.at(playerCounter) != "Benevolent" && commandList.at(playerCounter) != "Neutral" && commandList.at(playerCounter) != "Cheater") {
            command->saveEffect("Tournament command contains improper player strategy (" + commandList.at(playerCounter) + ")");
            return false;
        }

        ++playerCounter;
    }
    if (!nextIsGameNumber && commandList.at(playerCounter) != "-G") {
        command->saveEffect("Tournament command contains too many players or number of games does not follow players");
        return false;
    }

    // Where game number is specified
    int gameCounter = playerCounter  + 1;
    if (!isStringNumber(commandList.at(gameCounter))) {
        command->saveEffect("Number of games not a valid number");
        return false;
    }
    int numGames = stoi(commandList.at(gameCounter));
    if (numGames < 1 || numGames > 5) {
        command->saveEffect("Can only have between 1-5 games");
        return false;
    }

    // Where -D is specified
    int turnCounter = gameCounter + 1;
    if (commandList.at(turnCounter) != "-D") {
        command->saveEffect("Tournament command improperly formatted (Turn counter not where should be)");
        return false;
    }
    ++turnCounter;      // Where num is specified
    if (!isStringNumber(commandList.at(turnCounter))) {
        command->saveEffect("Number of turns not a valid number");
        return false;
    }
    int numTurns = stoi(commandList.at(turnCounter));
    if (numTurns < 10 || numTurns > 50) {
        command->saveEffect("Must specify between 10 and 50 turns per game");
        return false;
    }

    return true;
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

    string commandString = segmentList.front();

    if (commandString == "tournament") {
        return validateTournamentCommand(segmentList, command);
    }

    // There can only be two params
    if (segmentList.size() > 2)
    {
        command->saveEffect(command->getCommand() + " has too many parameters");

        return false;
    }

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
    return "Command: "+ this->savedCommand + "\n";
}

///
/// File Processor Adapter
///

/**
 * Default constructor.
*/
FileCommandProcessorAdapter::FileCommandProcessorAdapter() 
{
    this->fileReader = new FileLineReader();
}

/**
 * Constructor that takes a FileLineReader.
 *
 * @param file FileLineReader to set current fileReade to
*/
FileCommandProcessorAdapter::FileCommandProcessorAdapter(FileLineReader* file) 
{
    this->fileReader = file;
}

/**
 * Copy constructor. Sets fileReader to input's fileReader
 *
 * @param adapter FileCommandProcessorAdapter to copy
*/
FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter& adapter) {
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