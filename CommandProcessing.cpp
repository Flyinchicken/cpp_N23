#include "CommandProcessing.h"

#include <iostream>

using std::cin;
using std::endl;
using std::cout;

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
    cout << "Give a command:" << endl;
    string commandStr;
    cin >> commandStr;
    return commandStr;
}

void CommandProcessor::saveCommand(string command) {
    this->commandsList.push_back(new Command(command));
}

vector<string> CommandProcessor::getCommand() {
    string inputCommand = this->readCommand();
    this->saveCommand(inputCommand);
    vector<string> commands;
    commands.push_back(inputCommand);
    return commands;
}

vector<Command*> CommandProcessor::getCommandsList() {
    return this->commandsList;
}