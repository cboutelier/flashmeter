#ifndef SETTING_PAGE_H
#define SETTING_PAGE_H

#include "page.h"
#include "../../model/model.h"
#include "../areas/area.h"

class SettingPage : public Page
{

private:
    int selectedEntry = 0;
    void adjustSelectedEntry();
    bool isUpDownAllowed();
    Area *titleArea;
    Area *settingsListArea;
    void (*exitCallback)(void*);
    void *callingContext;

protected:
    //EntryRenderer *renderers;
    void buildAreas();

public:
    SettingPage(DisplayDevice *d, Model *model, ConsoleDelegator *console, char const *code);
    ~SettingPage();
    void onButtonEvent(const unsigned int button);
    void show();
    static void refreshCallback(void *this_pointer);
    void setExitCallback(  void (*exitCallback)(void*), void *context){ this->exitCallback = exitCallback; this->callingContext=context; };
};

#endif //SETTING_PAGE_H