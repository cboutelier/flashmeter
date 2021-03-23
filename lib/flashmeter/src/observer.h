#ifndef MY_OBSERVER_H
#define MY_OBSERVER_H

#include "observable.h"

class Observable;

class Observer
{
public:
    void attachSubject(Observable *modele);
    virtual void onReceiveDataFromSubject(const Observable *model) = 0;
};

#endif //MY_OBSERVER_H