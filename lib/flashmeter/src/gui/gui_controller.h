#ifndef GUI_H
#define GUI_H

#include "../model/model.h"
#include "../display/display_device.h"

class GuiController
{
public:
    GuiController(DisplayDevice* d, Model* model);
 
    int currentPage = 0;
    int usedPages = 0;

   
    void off();
    void on();
     
    void show();

    void onSettingClick();
    void onUpClick();
    void onDownClick();
    void onRightClick();
    void onLeftClick();
    bool onOkClick();
    bool onBackClick();


private:
    DisplayDevice *display;
    void showSplash();
    bool isOn;
    Model* model;
};

#endif