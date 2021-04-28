#ifndef FLASH_PAGE_H
#define FLASH_PAGE_H
#include "page.h"
#include "../areas/area.h"

class FlashPage : public Page
{

protected:
    void buildAreas();

public:
    FlashPage(DisplayDevice *d, Model *model, ConsoleDelegator *console, char const *code);
    ~FlashPage();
    void onButtonEvent(const unsigned int button);
    void show();

    
    Area* progressArea;
    Area* infoArea;
    Area* flashArea;
};

#endif //FLASH_PAGE_H