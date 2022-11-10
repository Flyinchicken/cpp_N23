#include "CommandProcessing.h"

#include <iostream>
#include <cctype>

using std::cin;
using std::endl;
using std::cout;
using std::ifstream;

//
//  COMMAND STRINGS
//

// Define command string constants
const string CommandStrings::validateMap = "validatemap";
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
        input == validateMap
        || input == gameStart
        || input == replay
        || input == quit;
}

/**
 * Stream insertion operator for CommandStrings. Will display current dictionary of command strings.
*/
ostream& operator << (ostream& out, const CommandStrings& strings) {
    out << "Current list of command strings: " << endl;

    // Done manually since could not find way to programmatically do it within C++ without the aid
    // of external libraries
    out << "1: " << "loadmap <filename>" << endl;
    out << "2: " << strings.validateMap << endl;
    out << "3: " << "addplayer <playername>" << endl;
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

CommandProcessor::CommandProcessor() {
    this->commandsList = vector<Command*>();
}

bool has_suffix(const std::string& str, const std::string& suffix)
{
    return str.size() >= suffix.size() &&
        str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

//Check if the valid command can be used in the current game state
bool validateCommandWithCurrentState(Command* command, GameStates currentGameState) {

    switch (currentGameState) {
    case START:
        if (command->getCommand().find("loadmap")) {
            return true;
        }
        break;
    case MAPLOADED:
        if (command->getCommand().find("loadmap") || command->getCommand() == CommandStrings::validateMap) {
            return true;
        }
        break;
    case MAPVALIDATED:
        if (command->getCommand().find("addplayer")) {
            return true;
        }
        break;
    case PLAYERSADDED:
        if (command->getCommand().find("addplayer") || command->getCommand() == CommandStrings::gameStart) {
            return true;
        }
        break;
    case WIN:
        if (command->getCommand() == CommandStrings::replay || command->getCommand() == CommandStrings::quit) {
            return true;
        }
        break;
    }

    command->saveEffect(command->getCommand() + " is not valid in the current game state");
    cout << command->getCommand() + " is not valid in the current game state" << endl;
    return false;
    
}

//Check if the valid command can be used in the current game state
bool CommandProcessor::validate(Command* command, GameStates currentGameState) {

    string commandString = command->getCommand();
    bool isCommandValid = false;
    const int loadmapStringSize = 7;
    const int addplayerStringSize = 9;

    bool isLoadmapCommand = commandString.find("loadmap") == 0 && (commandString.size() > loadmapStringSize) ? isspace(commandString.at(loadmapStringSize)) : false;
    bool isAddplayerCommand = commandString.find("addplayer") == 0 && (commandString.size() > addplayerStringSize) ? isspace(commandString.at(addplayerStringSize)) : false;


    //return true if the command given is in the list of valid commands
    if (CommandStrings::isStringCommandString(commandString)) isCommandValid = true;

    bool isLoadmapOrAddplayer = isLoadmapCommand || isAddplayerCommand;

    //return false if the command given is neither in the list of valid commands or a command to add a
    //player (addplayer) or load a map (loadmap)
    if (!isLoadmapOrAddplayer && !CommandStrings::isStringCommandString(commandString)) {
        command->saveEffect(commandString + " is not a valid command string!");
        cout << commandString + " is not a valid command string!" << endl;
    }

    //Check if the loadmap <filename> command has a valid filename
    if (isLoadmapCommand) {
        string mapFile = commandString.substr(loadmapStringSize + 1, commandString.size() - loadmapStringSize);
        ifstream infile(mapFile.c_str());
        if (mapFile != "" && infile.good() && has_suffix(mapFile, ".map")) {
            cout << "Loading map: " << mapFile << endl;
            isCommandValid = true;
        }
        else {
            command->saveEffect(commandString + " is not a valid command string. The Map file provided does not exist or is not a .map file.");
            cout << commandString + " is not a valid command string. The Map file provided does not exist or is not a .map file." << endl;
        }
    }
    //Check if the addplayer <playername> command has a playername
    else if (isAddplayerCommand) {
        string playerName = commandString.substr(addplayerStringSize + 1, commandString.size() - addplayerStringSize);
        if (playerName == "" || playerName.find_first_not_of(' ') == playerName.npos) {
            command->saveEffect(commandString + " is not a valid command string. There is no player name provided.");
            cout << commandString + " is not a valid command string. There is no player name provided." << endl;
        }
        else {
            cout << "Adding player: " << playerName << endl;
            isCommandValid = true;
        }
    }

    if (isCommandValid) {
        return validateCommandWithCurrentState(command, currentGameState);
    }
    return false;
}


void CommandProcessor::readCommand() {
    while(true){
        cout << "Give a command: (Type 'end' when you wish to stop) " << endl;
        string commandStr;
        getline(cin, commandStr);
        if (commandStr != "") {
            if(commandStr == "end"){
                return;
            }
            this->saveCommand(commandStr);
        }
    }
}

void CommandProcessor::saveCommand(string command) {
    this->commandsList.push_back(new Command(command));
}

void CommandProcessor::getCommand() {
    this->readCommand();
}

vector<Command*> CommandProcessor::getCommandsList() {
    return this->commandsList;
}

CommandProcessor::~CommandProcessor() {

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

void FileCommandProcessorAdapter::readCommand() {
    
    this->saveCommand("Openning file " + filePath);

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
