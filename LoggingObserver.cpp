#include "LoggingObserver.h"

Subject::Subject(){
    observers = new vector<Observer*>();
}

Subject::~Subject(){
    delete observers;
}

void Subject::attach(Observer* observer){
    observers->push_back(observer);
}

void Subject::detach(Observer* observer){
    for(int i = 0; i < observers->size(); i++){
        if(observers->at(i) == observer){
            observers->erase(observers->begin()+i);
        }
    }
}

void Subject::notify(Subject *subject){
    vector<Observer*>* observers = subject->observers;
    for (auto& observer : *observers) {
        observer->update(dynamic_cast<ILoggable*>(subject));
    }
}

Observer::~Observer(){}

Observer::Observer(){}

LogObserver::LogObserver(){
    outputfile.open("gamelog.txt",ios_base::app);
}

LogObserver::~LogObserver(){
    outputfile.close();
}

void LogObserver::update(ILoggable* subject){
    outputfile << subject->stringToLog();
}

void LogObserver::endOutput(){
    outputfile.close();
}