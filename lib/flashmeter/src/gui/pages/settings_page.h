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
    Area* titleArea; 

protected:
    //EntryRenderer *renderers;
    void buildAreas();

public:
    SettingPage(DisplayDevice *d, Model *model, ConsoleDelegator *console, char const *code);
    ~SettingPage();
    void onButtonEvent(const unsigned int button);
    void show();
};

#endif //SETTING_PAGE_H