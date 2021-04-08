#ifndef APERTURE_AREA_H
#define APERTURE_AREA_H



#include "area.h"
#include "../../console_delegator.h"

class ApertureArea : public Area
{

public:
    ApertureArea(DisplayDevice *d,ConsoleDelegator *console,  int x, int y, int width, int height);
    virtual void show();
    virtual void fillArea();
    virtual void onReceiveDataFromSubject(const Observable *model);
    int currentIndex = 0;

private:
    char const * getApertureFromIndex();
    char const *apertures[10];
    void buildApertures();
    ConsoleDelegator* console;
};

#endif //APERTURE_AREA_H