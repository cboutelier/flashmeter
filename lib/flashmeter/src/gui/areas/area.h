#ifndef AREA_H
#define AREA_H

#include "../../display/display_device.h"
#include "../../observer.h"
#include "../../model/model.h"

class Area : public Observer
{
public:
    Area(DisplayDevice *d, int x, int y, int width, int height);
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    bool hasFocus();
    void setFocus(bool b);

    unsigned int getBackground();
    unsigned int getForeground();
    void setBackground(unsigned int back);
    void setForeground(unsigned int fore);

    virtual void show() = 0;
    //virtual void fillArea() = 0;

    virtual void onReceiveDataFromSubject(const Observable *model) = 0;

protected:
    int x;
    int y;
    int width;
    int height;
    bool initDone = false;
    bool focus = false;

    unsigned int background;
    unsigned int foreground;
    DisplayDevice *display;

    int getRelativeX(int x);
    int getRelativeY(int y);
};

#endif //AREA_H