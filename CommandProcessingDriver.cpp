#include "CommandProcessing.h"
#include "CommandProcessingDriver.h"
#include <iostream>
using std::endl;
using std::cout;
using std::cin;


void testCommandProcessor() {

    while (true) {

        cout << "If you wish to create commands using the CONSOLE, type: -console\nIf you wish to create commands using a FILE, type: -file\nTo terminate, type: end" << endl;
        string input;
        getline(cin, input);

        if (input == "end") {
            return;
        }

        if (input == "-console") {

            //Test CommandProcessor
            CommandProcessor* console = new CommandProcessor();
            console->getCommand();
            vector<Command*> consoleCommands = console->getCommandsList();

            for (Command* i : consoleCommands) {    // 0 = false, 1 = true
                cout << "========================================" << endl;
                cout << "Command from console: " << i->getCommand() << endl;
                    cout << "Game state START: " << console->validate(i, START) << endl;
                    cout << "Game state MAPLOADED: " << console->validate(i, MAPLOADED) << endl;
                    cout << "Game state MAPVALIDATED: " << console->validate(i, MAPVALIDATED) << endl;
                    cout << "Game state PLAYERSADDED: " << console->validate(i, PLAYERSADDED) << endl;
                    cout << "Game state WIN: " << console->validate(i, WIN) << endl;
            }
        }
        else if (input == "-file") {
            cin.clear();
            //Test FileCommandProcessorAdapter
            FileCommandProcessorAdapter* file = new FileCommandProcessorAdapter();
            file->getCommand();
            vector<Command*> fileCommands = file->getCommandsList();

            for (Command* i : fileCommands) {   // 0 = false, 1 = true
                if (i->getCommand().find("Opening") == std::string::npos) {
                    cout << "========================================" << endl;
                    cout << "Command from file: " << i->getCommand() << endl;
                        cout << "Game state START: " << file->validate(i, START) << endl;
                        cout << "Game state MAPLOADED: " << file->validate(i, MAPLOADED) << endl;
                        cout << "Game state MAPVALIDATED: " << file->validate(i, MAPVALIDATED) << endl;
                        cout << "Game state PLAYERSADDED: " << file->validate(i, PLAYERSADDED) << endl;
                        cout << "Game state WIN: " << file->validate(i, WIN) << endl;
                }
            }
        }
        else {
            cout << "Invalid input" << endl;
        }
    }

}