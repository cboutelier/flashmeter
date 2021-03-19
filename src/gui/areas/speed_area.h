#ifndef SPEED_AREA_H
#define SPEED_AREA_H

#include <Arduino.h>

#include "area.h"

class SpeedArea : public Area
{

private:
    double speed;

public:
    using Area::Area;
    virtual void show();
    virtual void fillArea();
    void onReceiveDataFromSubject(const FlashMeterModel* model);
    String convertValue();
};

#endif //SPEED_AREA_H