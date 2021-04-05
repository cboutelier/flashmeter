#include "entry_renderer.h"
#include <string.h>
#include <stdio.h>

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
    char msg[50];
    if (entry->getCurrentValueIndex() < 0)
    {
        sprintf(msg, "%s : ---", entry->getEntryName());
    }
    else
    {
        sprintf(msg, "%s : %s", entry->getEntryName(), entry->getValue(entry->getCurrentValueIndex()));
    }
    display->print(msg);
}
