#ifndef PAGE_H
#define PAGE_H
#include <Arduino.h>
#include <TFT_eSPI.h>
#include "../flashmeter_model.h"

class Page
{

private:


protected:
    TFT_eSPI *display;
    String code;
    FlashMeterModel* model;

public:
    Page();
    virtual void onUp() = 0;
    virtual void onDown() = 0;
    virtual void onLeft() = 0;
    virtual void onRight() = 0;
    virtual bool onOk() = 0;
    String *lines;
    void setDisplay(TFT_eSPI *display);
    String getCode() { return this->code; }

    virtual void show() = 0;
    virtual void declineYourId();
};

#endif //PAGE_H