#ifndef INFO_AREA_H
#define INFO_AREA_H

#include "area.h"
#include "../../console_delegator.h"

class TitleArea : public Area
{

private:
    ConsoleDelegator *console;

protected:
public:
    TitleArea(DisplayDevice *d, ConsoleDelegator *console, int x, int y, int width, int height);
    virtual void show();
    virtual void fillArea();
    virtual void onReceiveDataFromSubject(const Observable *model);
};

#endif //INFO_AREA_H