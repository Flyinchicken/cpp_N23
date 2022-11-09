#include "CommandProcessing.h"

#include <iostream>
#include <sstream>

using std::cin;
using std::endl;
using std::cout;
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
bool CommandStrings::isStringCommandString(string input) {
    return 
        input == loadMap
        || input == validateMap
        || input == addPlayer
        || input == gameStart
        || input == replay
        || input == quit;
}

/**
 * Stream insertion operator for CommandStrings. Will display current dictionary of command strings.
*/
ostream &operator << (ostream &out, const CommandStrings &strings) {
    out << "Current list of command strings: " << endl;

    // Done manually since could not find way to programmatically do it within C++ without the aid
    // of external libraries
    out << "1: " << strings.loadMap + " <filename>" << endl;
    out << "2: " << strings.validateMap << endl;
    out << "3: " << strings.addPlayer + " <playername>" << endl;
    out << "4: " << strings.gameStart << endl;
    out << "5: " << strings.replay << endl;
    out << "6: " << strings.quit << endl;

    return out;
}

//
//  COMMAND
//

Command::Command() {
    this->command = "";
    this->effect = "";
}

Command::Command(string commandString) {
    this->command = commandString;
    this->effect = "";
}

Command::~Command() {
    // Nothing to delete...for now
}

string Command::getCommand() {
    return this->command;
}

void Command::saveEffect(string effectString) {
    this->effect = effectString;
}

string Command::getEffect() {
    return this->effect;
}


//
//  COMMAND PROCESSOR
//

/**
 * Default constructor that initializes the internal command List
*/
CommandProcessor::CommandProcessor() {
    this->commandsList = vector<Command*>();
}

CommandProcessor::~CommandProcessor() {

}

/**
 * Gets a command string from the user via the console
 * 
 * @returns The command string input from console
*/
string CommandProcessor::readCommand() {
    string commandStr;

    getline(cin, commandStr);

    return commandStr;
}

/**
 * Turns a command string into a Command object and adds it to the command list.
 * 
 * @param command The command string to add as a Command to the internal list
*/
void CommandProcessor::saveCommand(string command) {
    this->commandsList.push_back(new Command(command));
}

/**
 * Gets an input command from the user via the console, and saves it in the internal Command list.
 * 
 * @returns The command string as a Command object 
*/
Command* CommandProcessor::getCommand() {
    string inputString = this->readCommand();

    this->saveCommand(inputString);

    return this->commandsList.back();
}

/**
 * Gets the type of input format the user would like (from the console or a file) from the console.
*/
void CommandProcessor::getInputFormat() {
    cout << "Input -console if you would like to input commands via the console" << endl;
    cout << "Input -file <filename> if you would like commands to be input via an existing file" << endl;

    bool gettingInputFormat = true;

    while (gettingInputFormat) {
        string inputFormat = this->readCommand();

        if (inputFormat == "-console") {
            this->consoleInput = true;
            return;
        }

        vector<string> inputSegments = this->splitStringByDelim(inputFormat, ' ');
        if (inputSegments.size() == 2 && inputSegments.front() == "-file") {
            // TODO: file processing and name storage
            this->consoleInput = false;
            return;
        }
        
        cout << "Invalid input format!" << endl;        
    }
}

/**
 * If commands are taken from the console or a file.
 * 
 * @returns Whether or not the user has decided to input commands via the console
*/
bool CommandProcessor::isConsoleInput() {
    return this->consoleInput;
}

/**
 * Splits a string by a char delimeter.
 * 
 * @param toSplit The string to split into pieces
 * @param delim The char delimeter - where to split the string
 * @returns A vector<string> of all the pieces of the string
*/
vector<string> CommandProcessor::splitStringByDelim(string toSplit, char delim) {
    stringstream commandStream(toSplit);
    vector<string> segmentList;
    string segment;

    while (getline(commandStream, segment, delim)) {
        segmentList.push_back(segment);
    }

    return segmentList;
}

bool has_suffix(const std::string& str, const std::string& suffix)
{
    return str.size() >= suffix.size() &&
        str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

bool validateLoadmapAndAddplayer(Command* command) {

    bool isLoadmapCommand = command->getCommand().find("loadmap") != std::string::npos;
    bool isAddplayerCommand = command->getCommand().find("addplayer") != std::string::npos;

    const int loadmapSize = 7;
    const int addplayerSize = 9;

    if (!isLoadmapCommand && !isAddplayerCommand) return true;

    //Check if the loadmap <filename> command has a valid filename
    if (isLoadmapCommand) {
        string mapFile = command->getCommand().substr(loadmapSize, command->getCommand().size() - loadmapSize);
        mapFile.erase(0, 1); //remove extra white space if string not empty
        ifstream infile(mapFile.c_str());
        if (mapFile != "" && infile.good() && has_suffix(mapFile, ".map")) {
            return true;
        }
        else {
            command->saveEffect(command->getCommand() + " is not a valid command string. The Map file provided does not exist or is not a .map file.");
            cout << command->getCommand() + " is not a valid command string. The Map file provided does not exist or is not a .map file." << endl;
            return false;
        }
    }
    //Check if the addplayer <playername> command has a playername
    else if (isAddplayerCommand) {
        string playerName = command->getCommand().substr(addplayerSize, command->getCommand().size() - addplayerSize);
        playerName.erase(0, 1); //remove extra white space if string not empty
        if (playerName == "") {
            command->saveEffect(command->getCommand() + " is not a valid command string. There is no player name provided.");
            cout << command->getCommand() + " is not a valid command string. There is no player name provided." << endl;
            return false;
        }
        else {
            return true;
        }
    }
}

bool CommandProcessor::validate(Command *command, GameStates currentGameState) {
    // Separate string by <Space> (could parse whitespaces at the end if need be)
    stringstream commandStream(command->getCommand());
    vector<string> segmentList;
    string commandSegment;

    while (getline(commandStream, commandSegment, ' ')) {
        segmentList.push_back(commandSegment);
    }

    // There can only be two params
    if (segmentList.size() > 2) {
        command->saveEffect(command->getCommand() + " has too many parameters");

        return false;
    }
    
    string commandString = segmentList.front();

    // Check to make sure 1st param is a valid command
    if (!CommandStrings::isStringCommandString(commandString)) {
        command->saveEffect(commandString + " is not a valid command string");

        return false;
    }

    // Check to make sure has correct params
    if ((commandString == CommandStrings::loadMap || commandString == CommandStrings::addPlayer) && segmentList.size() != 2) {
        command->saveEffect(commandString + " must have only one valid parameter, separated by a white space");

        return false;
    }
    if (commandString != CommandStrings::loadMap && commandString != CommandStrings::addPlayer && segmentList.size() != 1) {
        command->saveEffect(commandString + " cannot have any parameters");

        return false;
    }

    // Check is valid in gamestate
    switch (currentGameState) {
        case START:
            if (commandString == CommandStrings::loadMap) {
                string mapFile = segmentList.back();
                string mapPath = "./MapFiles/" + mapFile;
                ifstream infile(mapFile.c_str());        
                if (mapFile == "" || infile.bad() || !has_suffix(mapFile, ".map")) {
                    command->saveEffect(mapFile + " is not a valid .map file or does not exist");
                    break;
                }

                return true;
            }
            break;
        case MAPLOADED:
            if (commandString == CommandStrings::loadMap || commandString == CommandStrings::validateMap) {
                if (commandString == CommandStrings::loadMap) {
                    // This is repeated
                    string mapFile = segmentList.back();
                    string mapPath = "./MapFiles/" + mapFile;
                    ifstream infile(mapFile.c_str());        
                    if (mapFile == "" || infile.bad() || !has_suffix(mapFile, ".map")) {
                        command->saveEffect(mapFile + " is not a valid .map file or does not exist");
                        break;
                    }
                }
                
                return true;
            }
            break;
        case MAPVALIDATED:
            if (commandString == CommandStrings::addPlayer) {
                return true;
            }
            break;
        case PLAYERSADDED:
            if (commandString == CommandStrings::addPlayer || commandString == CommandStrings::gameStart) {
                return true;
            }
            break;
        case WIN:
            if (commandString == CommandStrings::replay || commandString == CommandStrings::quit) {
                return true;
            }
            break;
        default:
            command->saveEffect(command->getCommand() + " is not valid in the current game state");
    }    

    return false;
}






vector<Command*> CommandProcessor::getCommandsList() {
    return this->commandsList;
}

/*
File Processor Adapter

*/

FileCommandProcessorAdapter::FileCommandProcessorAdapter() {
    CommandProcessor();
    this->fileReader = new FileProcessor();
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(FileProcessor* file) {
    CommandProcessor();
    this->fileReader = file;
}

FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {

}

string FileCommandProcessorAdapter::readCommand() {
    cout << "Type the path of the file where your commands are: (Type 'end' to stop)" << endl;
    string path;
    getline(cin, path);
    if (path == "") {
        getline(cin, path);
    }

    if (path == "end") {
        return path;
    }

    ifstream input(path);

    while (input.fail() && path != "")
    {
        if (path == "end") {
            return path;
        }
        input.clear();
        cout << "Incorrect file path. Please provide a valid file." << endl;
        getline(cin, path);
        input.open(path);
    }
    input.clear();

    vector<string> commands;
    commands = this->fileReader->processCommands(path);

    for (string i : commands)
        this->saveCommand(i);

    return "Opening " + path;
}


/*
File Processor

*/

FileProcessor::FileProcessor() {

}

FileProcessor::~FileProcessor() {
   
}

vector<string> FileProcessor::processCommands(string filePath) {

    vector<string> commands;
    string tempCommand;

    ifstream commandFile(filePath);

    while (getline(commandFile, tempCommand)) {
        commands.push_back(tempCommand);
    }

    commandFile.close();
    return commands;
}

