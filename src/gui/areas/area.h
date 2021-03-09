#ifndef AREA_H
#define AREA_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include "../observer.h"

class Area : public Observer
{
public:
    Area(int x, int y, int width, int height);
    int getX();
    int getY();
    int getWidth();
    int getHeight();

    uint32_t getBackground();
    uint32_t getForeground();
    void setBackground(uint32_t back);
    void setForeground(uint32_t fore);

    void setDisplay(TFT_eSPI *display);
    virtual void show() = 0;

    virtual void onReceiveDataFromSubject(const FlashMeterModel* model) = 0;

protected:
    int x;
    int y;
    int width;
    int height;
    String value;
    uint32_t background;
    uint32_t foreground;
    TFT_eSPI *display;
};

#endif //AREA_H