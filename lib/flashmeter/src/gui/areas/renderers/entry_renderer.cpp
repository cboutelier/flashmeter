#include "entry_renderer.h"
#include <string.h>
#include <stdio.h>
#include "../icons/flash.xbm"

EntryRenderer::EntryRenderer(DisplayDevice *display, Entry *entry, int relativeX, int relativeY, int index)
{

    this->display = display;
    this->entry = entry;

    this->areaBaseX = relativeX;
    this->areaBaseY = relativeY;
    this->index = index;
};

void EntryRenderer::show()
{
    display->setCursor(10, areaBaseY + 8 + index * 20, 2);

    if (entry->isSelected())
    {
        display->setTextColor(this->background_color, this->foreground_color);
    }

    display->print(entry->getEntryName());

    char msg[50];
    display->setTextColor(this->foreground_color, this->background_color);

    if (entry->getCurrentValueIndex() < 0)
    {
        sprintf(msg, " : ---");
    }
    else
    {
        sprintf(msg, " : %s", entry->getValue(entry->getCurrentValueIndex()));
      //  display->drawXBitmap( 10,50, flash_bits, flashbits_width,flashbits_height, TFT_GOLD, TFT_BLACK );
    }
    display->print(msg);
}

void EntryRenderer::setInitialColors(unsigned int background, unsigned int foreground, unsigned int selected)
{
    this->background_color = background;
    this->foreground_color = foreground;
    this->selected_color = selected;
}
