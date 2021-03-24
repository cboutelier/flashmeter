#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H
#include "page.h"
#include "../areas/area.h"

class MainPage : public Page
{

protected:
    void buildAreas();

public:
    MainPage(DisplayDevice *d, Model *model, ConsoleDelegator *console, char const *code);
    ~MainPage();
    void onButtonEvent(const unsigned int button);
    void show();

    Area* apertureArea;
    /*    Area* speedArea;
        Area* infoArea;*/
};

#endif //MAIN_PAGE_H