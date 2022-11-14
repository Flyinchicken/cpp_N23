#include "LoggingObserverDriver.h"
#include "Orders.h"
#include "CommandProcessing.h"
#include "GameEngine.h"

Chicken::Chicken()
{
    name = "Test chicken";
    age = 5;
}

Chicken::~Chicken() {}

void Chicken::scream()
{
    cout << "Chicken screaming" << endl;
    notify(this);
}

string Chicken::stringToLog()
{
    return (name + "\n");
}

void testLoggingObserver()
{
    LogObserver *gameLog = new LogObserver();
    Chicken *myChicken = new Chicken();
    myChicken->attach(gameLog);
    myChicken->scream();
    myChicken->scream();
    myChicken->scream();
    myChicken->scream();
    myChicken->scream();
    myChicken->scream();
    myChicken->scream();
    gameLog->endOutput();

    // CommandProcessor *cp = new CommandProcessor();
    // cp->attach(gameLog);
    // cp->getCommand();
}

// int main(){
//      testLoggingObserver();
//  }
