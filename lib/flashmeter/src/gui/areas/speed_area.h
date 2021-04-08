#ifndef SPEED_AREA_H
#define SPEED_AREA_H

#define SPEED_ARRAY_SIZE 30

#include "area.h"
#include "../../console_delegator.h"

class SpeedArea : public Area
{

public:
    SpeedArea(DisplayDevice *d,ConsoleDelegator *console,  int x, int y, int width, int height);
    virtual void show();
    virtual void fillArea();
    virtual void onReceiveDataFromSubject(const Observable *model);
     

private:
    ConsoleDelegator* console;
     char const *speeds[SPEED_ARRAY_SIZE];
    int index = -1;
    double speed;
    char const * convertToStringValue();
    void buildSpeeds();
};

#endif //SPEED_AREA_H