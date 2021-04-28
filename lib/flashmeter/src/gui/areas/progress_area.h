#ifndef PROGRESS_AREA_H
#define PROGRESS_AREA_H

 

#include "area.h"
#include "../../console_delegator.h"

class ProgressArea : public Area
{

public:
    ProgressArea(DisplayDevice *d,ConsoleDelegator *console,  int x, int y, int width, int height);
    virtual void show();
    virtual void fillArea();
    virtual void onReceiveDataFromSubject(const Observable *model); 

private:
    ConsoleDelegator* console;    
    double current =  0.1; 
};

#endif //PROGRESS_AREA_H