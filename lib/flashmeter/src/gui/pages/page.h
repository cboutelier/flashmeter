#ifndef PAGE_H
#define PAGE_H

#include "../../model/model.h"
#include "../../display/display_device.h"
#include "../../console_delegator.h"

class Page
{

private:
protected:
    DisplayDevice *display;
    char const *code;
    Model *model;
    ConsoleDelegator *console;
    
    virtual void buildAreas() = 0;

public:
    Page(DisplayDevice *d, Model *model, ConsoleDelegator *console, char const *code);
    virtual ~Page();
    virtual void onButtonEvent( const unsigned int button) = 0;
    virtual void show() = 0;

    char const *getCode() { return this->code; }
};

#endif //PAGE_H