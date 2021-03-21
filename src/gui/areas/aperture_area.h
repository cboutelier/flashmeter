#ifndef APERTURE_AREA_H
#define APERTURE_AREA_H

#include <Arduino.h>

#include "area.h"

class ApertureArea : public Area
{

public:
    ApertureArea(int x, int y, int width, int height);
    virtual void show();
    virtual void fillArea();
    void onReceiveDataFromSubject(const FlashMeterModel *model);
    int currentIndex = 0;

private:
    String getApertureFromIndex();
    String apertures[10];
    void buildApertures();
};

#endif //APERTURE_AREA_H