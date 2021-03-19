#ifndef APERTURE_AREA_H
#define APERTURE_AREA_H

#include <Arduino.h>

#include "area.h"

class ApertureArea : public Area
{

public:
    using Area::Area;
    virtual void show();
    virtual void fillArea();
    void onReceiveDataFromSubject(const FlashMeterModel *model);
    int currentIndex = 0;

private:
    String getApertureFromIndex();
};

#endif //APERTURE_AREA_H