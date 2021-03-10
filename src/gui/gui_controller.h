#ifndef GUI_H
#define GUI_H
#include <Arduino.h>
#include <TFT_eSPI.h>
#include "pages/page.h"
#include "flashmeter_model.h"

class GuiController
{
public:

    FlashMeterModel* model;

    Page* page;
    Page* settingPage;
    Page* mainPage;
    
    int currentPage = 0;
    int usedPages = 0;

    GuiController(TFT_eSPI* d, FlashMeterModel* model);
    void setLux(float lux);
    void off();
    void on();
    void addPage(Page* p);
    void show();

    void onSettingClick();
    void onUpClick();
    void onDownClick();
    void onRightClick();
    void onLeftClick();
    bool onOkClick();
    bool onBackClick();

    void buildMainPage();
 

private:
    TFT_eSPI *display;
    void showSplash();
    bool isOn;
};

#endif