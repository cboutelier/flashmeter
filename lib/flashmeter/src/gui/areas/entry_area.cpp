#include "entry_area.h"
#include <string.h>
#include <stdio.h>

EntryArea::EntryArea(DisplayDevice *d, ConsoleDelegator *console, int x, int y, int width, int height) : Area(d, x, y, width, height)
{
    this->console = console;
}

EntryArea::~EntryArea()
{

}

void EntryArea::show()
{
    int height = 15;
    int totalHeight= height*this->valuesCount +10;
    int baseY = (this->height-this->y - totalHeight)/2;
    display->fillRect(this->x, baseY, this->width, totalHeight, this->foreground);
    
    for (int j = 0; j < this->valuesCount; j++)
    {
        if (this->currentIndex == j)
        {
            display->setTextColor(this->foreground, this->background);
            display->fillRect(this->x,baseY + j * height + 5, this->width, height, this->background);
        }
        else
        {
            display->setTextColor(this->background, this->foreground);
            display->fillRect(this->x, baseY + j * height +5, this->width, height, this->foreground);
        }
        display->setCursor(this->x + 5, baseY + j * height + 5, 2);
        //display->setTextSize(2);
        display->print(this->values[j]);
        // this->console->println(this->values[j]);
    }
}

void EntryArea::fillArea()
{
   // display->fillRect(this->x, this->y, this->width, this->height, this->background);
   // display->setTextColor(this->foreground, this->background);
}

void EntryArea::onReceiveDataFromSubject(const Observable *m)
{
}

void EntryArea::onOk()
{
    this->callback(this->currentIndex, settingsArea);
}

void EntryArea::onDown()
{
    if (this->currentIndex < this->valuesCount)
    {
        this->currentIndex++;
        this->show();
    }
}

void EntryArea::onUp()
{
    if (this->currentIndex > 0)
    {
        this->currentIndex--;
        this->show();
    }
}