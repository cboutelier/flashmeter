#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#define MAX_REGISTERED_OBSERVERS 4

#include "observer.h"

class Observer;

class Observable
{

private:
    Observer *observers[MAX_REGISTERED_OBSERVERS];
    int registeredObservers = 0;

public:
    virtual void registerObserver(Observer *observer) = 0;
    virtual void unRegisterObserver(Observer *observer) =0;
};

#endif //OBSERVABLE_H