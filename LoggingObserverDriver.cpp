#include "LoggingObserverDriver.h"

Chicken::Chicken()
{
    name = "Test chicken";
    age = 5;
}

Chicken::~Chicken() {}

void Chicken::scream()
{
    cout << "Chicken screaming" << endl;
    notify();
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
}

// int main(){
//     testLoggingObserver();
// }
