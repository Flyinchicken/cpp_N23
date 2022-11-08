#include "CommandProcessing.h"

#include <iostream>

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
ostream &operator << (ostream &out, const CommandStrings &strings) {
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

    bool isLoadmapOrAddplayer = (command->getCommand().find("loadmap") != std::string::npos) || (command->getCommand().find("addplayer") != std::string::npos);

    if (!isLoadmapOrAddplayer && !CommandStrings::isStringCommandString(command->getCommand())) {
        command->saveEffect(command->getCommand() + " is not a valid command string!");
        cout << command->getCommand() + " is not a valid command string!"  << endl;
        return false;
    }


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

    return false;
}


string CommandProcessor::readCommand() {
    cout << "Give a command: (Type 'end' when you wish to stop) " << endl;
    string commandStr;
    getline(cin, commandStr);
    if (commandStr == "") {
        getline(cin, commandStr);
    }
    return commandStr;
}

void CommandProcessor::saveCommand(string command) {
    this->commandsList.push_back(new Command(command));
}

void CommandProcessor::getCommand() {
    while (true) {
        string inputCommand = this->readCommand();
        
        cout << inputCommand << endl;

        if (inputCommand == "end") {
            return;
        }

        this->saveCommand(inputCommand);
    }
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

