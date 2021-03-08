#ifndef MY_OBSERVER_H
#define MY_OBSERVER_H

#include <Arduino.h>

class FlashMeterModel;
 
class Observer
{
public:
    void attachSubject(FlashMeterModel *modele);
    virtual void onReceiveDataFromSubject(const FlashMeterModel* model) = 0;
};

#endif //MY_OBSERVER_H