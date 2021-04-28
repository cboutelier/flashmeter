#ifndef FLASH_AREA_H
#define FLASH_AREA_H

 

#include "area.h"
#include "../../console_delegator.h"

class FlashArea : public Area
{

public:
    FlashArea(DisplayDevice *d,ConsoleDelegator *console,  int x, int y, int width, int height);
    virtual void show();
    virtual void fillArea();
    virtual void onReceiveDataFromSubject(const Observable *model); 

private:
    ConsoleDelegator* console;    
     
};

#endif //FLASH_AREA_H