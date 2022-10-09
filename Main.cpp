#include "GameEngineDriver.h"

#include <iostream>
#include "MapDriver.h"

using namespace std;
int main()
{
    std::cout << "Welcome everyone!" << std::endl;
    
    MapDriver mapDriver;
    mapDriver.run();

    // Game Engine Tests
    std::cout << std::endl << "Game Engine Tests Commencing" << std::endl << std::endl;

    testGameStates();
}