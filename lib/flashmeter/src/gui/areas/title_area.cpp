#include "title_area.h"
#include "../../model/model.h"

#include <stdio.h>
#include <string.h>
#include "icons/settings_32.xbm"

TitleArea::TitleArea(DisplayDevice *d, ConsoleDelegator *console, int x, int y, int width, int height) : Area(d, x, y, width, height)
{
    this->console = console;
}

void TitleArea::fillArea()
{
    display->fillRect(this->x, this->y, this->width, this->height, this->background);
    this->initDone = true;
}

void TitleArea::show()
{
    if (!this->initDone)
    {
        this->fillArea();
    }
    display->setTextColor(this->foreground, this->background);
    display->setCursor( 60, 10, 4);
    display->drawXBitmap(10, 4, settings_32px_bits, 32, 32, TFT_WHITE, TFT_GOLD);
    display->print("SETTINGS");

 }

void TitleArea::onReceiveDataFromSubject(const Observable *observable)
{
   //Do nothing
}

 
 
