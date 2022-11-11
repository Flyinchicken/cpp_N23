#pragma once
#include <fstream>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

class ILoggable {
    public:
    virtual string stringToLog() = 0;
};

class Observer{
    public:
    ~Observer();
    virtual void update(ILoggable* subject) = 0;

    protected:
    Observer();
};

class Subject{
    private:
    vector<Observer*> *observers;

    public:
    Subject();
    ~Subject();
    virtual void attach(Observer* observer);
    virtual void detach(Observer* observer);
    virtual void notify();
};






class LogObserver : public Observer{
    public:
    LogObserver();
    ~LogObserver();
    void update(ILoggable* subject);
    void endOutput();

    private:
    ofstream outputfile;
};

