#include "progress_area.h"
#include <string.h>
#include <stdio.h>

ProgressArea::ProgressArea(DisplayDevice *d, ConsoleDelegator *console, int x, int y, int width, int height) : Area(d, x, y, width, height)
{
    this->console = console;
    
}

void ProgressArea::show()
{
    display->fillRect(this->x, this->y, this->width, this->height, this->background);
    display->setTextColor(this->foreground, this->background);

    display->drawRect(this->x + 10, this-> y + 5, this->width - 20, this->height -10,this->foreground );

    display->fillRect(this->x + 12, this-> y + 7, (this->width - 16) * this->current, this->height -14, this->foreground);
    
}

void ProgressArea::fillArea()
{
    display->fillRect(this->x, this->y, this->width, this->height, this->background);
    display->setTextColor(this->foreground, this->background);
}

void ProgressArea::onReceiveDataFromSubject(const Observable *m)
{
    Model *model = (Model *)m;
     
}
