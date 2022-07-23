#include "flash_area.h"
#include <string.h>
#include <stdio.h>

FlashArea::FlashArea(DisplayDevice *d, ConsoleDelegator *console, int x, int y, int width, int height) : Area(d, x, y, width, height)
{
    this->console = console;
}

void FlashArea::show()
{
    display->fillRect(this->x, this->y, this->width, this->height, this->background);
    display->setTextColor(this->foreground, this->background);
}

void FlashArea::fillArea()
{
    display->fillRect(this->x, this->y, this->width, this->height, this->background);
    display->setTextColor(this->foreground, this->background);
}

void FlashArea::onReceiveDataFromSubject(const Observable *m)
{
    Model *model = (Model *)m;
}