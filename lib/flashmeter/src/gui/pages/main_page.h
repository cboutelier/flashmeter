#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H
#include "page.h"

class MainPage : public Page
{

protected:
    void show();
    void buildAreas();

public:
    MainPage(DisplayDevice *d, Model *model, ConsoleDelegator *console, char const *code);
    ~MainPage();
    void onButtonEvent();

    /* Area* apertureArea;
        Area* speedArea;
        Area* infoArea;*/
};

#endif //MAIN_PAGE_H