#ifndef SPEED_AREA_H
#define SPEED_AREA_H

#include <Arduino.h>

#include "area.h"

class SpeedArea : public Area
{

public:
    using Area::Area;
    virtual void show();
    void onReceiveDataFromSubject(const FlashMeterModel* model);
};

#endif //SPEED_AREA_H