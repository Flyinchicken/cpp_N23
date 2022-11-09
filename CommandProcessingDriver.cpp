#include "CommandProcessing.h"
#include "CommandProcessingDriver.h"
#include <iostream>
using std::endl;
using std::cout;
using std::cin;

void testCommandProcessor() {
    bool testInProgress = true;

    while (testInProgress) {
        CommandProcessor *processor = new CommandProcessor();

        processor->getInputFormat();

        cout << processor->isConsoleInput() << endl;

        delete processor;
    }
}

// void testCommandProcessor() {

//     while (true) {

//         cout << "If you wish to create commands using the CONSOLE, type: -console\nIf you wish to create commands using a FILE, type: -file\nTo terminate, type: end" << endl;
//         string input;
//         getline(cin, input);

//         if (input == "end") {
//             return;
//         }

//         if (input == "-console") {

//             //Test CommandProcessor
//             CommandProcessor* console = new CommandProcessor();
//             console->getCommand();
//             vector<Command*> consoleCommands = console->getCommandsList();

//             for (Command* i : consoleCommands) {    // 0 = false, 1 = true
//                 cout << "========================================" << endl;
//                 cout << "Command from console: " << i->getCommand() << endl;
//                 if (validateLoadmapAndAddplayer(i)) {
//                         cout << "START: " << console->validate(i, START) << endl;
//                         cout << "MAPLOADED: " << console->validate(i, MAPLOADED) << endl;
//                         cout << "MAPVALIDATED: " << console->validate(i, MAPVALIDATED) << endl;
//                         cout << "PLAYERSADDED: " << console->validate(i, PLAYERSADDED) << endl;
//                         cout << "WIN: " << console->validate(i, WIN) << endl; 
//                 }

//             }
//         }
//         else if (input == "-file") {
//             cin.clear();
//             //Test FileCommandProcessorAdapter
//             FileCommandProcessorAdapter* file = new FileCommandProcessorAdapter();
//             file->getCommand();
//             vector<Command*> fileCommands = file->getCommandsList();

//             for (Command* i : fileCommands) {   // 0 = false, 1 = true
//                 if (i->getCommand().find("Opening") == std::string::npos) {
//                     cout << "========================================" << endl;
//                     cout << "Command from file: " << i->getCommand() << endl;
//                     if (validateLoadmapAndAddplayer(i)) {
//                         cout << "START: " << file->validate(i, START) << endl;
//                         cout << "MAPLOADED: " << file->validate(i, MAPLOADED) << endl;
//                         cout << "MAPVALIDATED: " << file->validate(i, MAPVALIDATED) << endl;
//                         cout << "PLAYERSADDED: " << file->validate(i, PLAYERSADDED) << endl;
//                         cout << "WIN: " << file->validate(i, WIN) << endl;
//                     }
//                 }
//             }
//         }
//         else {
//             cout << "Invalid input" << endl;
//         }
//     }

// }