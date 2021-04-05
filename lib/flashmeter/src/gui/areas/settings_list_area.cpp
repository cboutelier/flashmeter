#include "settings_list_area.h"
#include "../../model/model.h"

#include <stdio.h>
#include <string.h>
#include "renderers/entry_renderer.h"

SettingsListArea::SettingsListArea(DisplayDevice *d, ConsoleDelegator *console, int x, int y, int width, int height) : Area(d, x, y, width, height)
{
    this->console = console;
}

SettingsListArea::~SettingsListArea()
{
    if (entries != nullptr)
    {
        delete entries;
    }
}

void SettingsListArea::fillArea()
{
    display->fillRect(this->x, this->y, this->width, this->height, this->background);
    this->initDone = true;
}

void SettingsListArea::show()
{
    if (!this->initDone)
    {
        this->fillArea();
    }
    display->setTextColor(this->foreground, this->background);

    this->displayEntries();
}

void SettingsListArea::onReceiveDataFromSubject(const Observable *observable)
{
    //Do nothing
}

void SettingsListArea::displayEntries()
{

    if (entries != nullptr)
    {
        for (int i = 0; i < 3; i++)
        {
            if (this->entries[i] != nullptr)
            {
                this->displayEntry(this->entries[i], i);
            }
        }
    }
}

void SettingsListArea::displayEntry(Entry *entry, int index)
{
    if (entry != nullptr)
    {
        EntryRenderer* renderer = new EntryRenderer(this->display, entry, getRelativeY(0), getRelativeY(0), index) ;
        renderer->show();
       
    }
}

void SettingsListArea::initEntries(const int number)
{
    this->entries = new Entry *[number];
    for (int i = 0; i < number; i++)
    {
        this->entries[i] = nullptr;
    }
}

void SettingsListArea::addEntry(Entry *entry, const int index)
{
    this->entries[index] = entry;
}
