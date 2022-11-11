#include "LoggingObserver.h"

void testLoggingObserver();

/**
 * Testing subject for LogObserver since part 1 has not been finalized yet and I love chickens
*/
class Chicken : public ILoggable, public Subject{
    public:
    Chicken();
    ~Chicken();
    void scream();   // pure virtual method from the ILoggable class
    string stringToLog();
    private:
    string name;
    int age;
};
