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
    return input == loadMap
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
    out << "1: " << strings.loadMap << endl;
    out << "2: " << strings.validateMap << endl;
    out << "3: " << strings.addPlayer << endl;
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

bool CommandProcessor::validate(Command *command, GameStates currentGameState) {
    if (!CommandStrings::isStringCommandString(command->getCommand())) {
        command->saveEffect(command->getCommand() + " is not a valid command string!");
        cout << command->getCommand() + " is not a valid command string!"  << endl;
        return false;
    }
    
    switch(currentGameState) {
        case START:
            if (command->getCommand() == CommandStrings::loadMap) {
                return true;
            }
            break;
        case MAPLOADED:
            if (command->getCommand() == CommandStrings::loadMap || command->getCommand() == CommandStrings::validateMap) {
                return true;
            }
            break;
        case MAPVALIDATED:
            if (command->getCommand() == CommandStrings::addPlayer) {
                return true;
            }
            break;
        case PLAYERSADDED:
            if (command->getCommand() == CommandStrings::addPlayer || command->getCommand() == CommandStrings::gameStart) {
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
    cin >> commandStr;
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

