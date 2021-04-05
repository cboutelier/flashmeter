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
        EntryRenderer *renderer = new EntryRenderer(this->display, entry, getRelativeY(0), getRelativeY(0), index);
        renderer->setInitialColors(this->background, this->foreground, TFT_WHITE);
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
    this->entryCount = index + 1;
}

void SettingsListArea::onButtonEvent(const unsigned int button)
{

    int entrySelectedIndex = -1;
    for (int i = 0; i < entryCount; i++)
    {
        if (this->entries[i] != nullptr && this->entries[i]->isSelected())
        {
            entrySelectedIndex = i;
            break;
        }
    }

    if (button == 1)
    {
        onUp(entrySelectedIndex);
    }
    else if (button == 2)
    {
        onDown(entrySelectedIndex);
    }
    else if (button == 3)
    {
        //LEFT
    }
    else if (button == 4)
    {
        //RIGHT
    }
    displayEntries();
}

void SettingsListArea::onDown(int currentSelectedIndex)
{
    this->console->println("On button down");

    if (currentSelectedIndex == -1)
    {
        this->entries[0]->select();
        displayEntries();
        this->console->println("Select the first and show");
        return;
    }
    int entrySelectedIndex = currentSelectedIndex;

    char msg[50];
    sprintf(msg, "%i  %i ", entrySelectedIndex, this->entryCount);
    this->console->println(msg);

    if (entrySelectedIndex < (entryCount - 1))
    {
        this->console->println("Button pressed and toggle selection");
        this->entries[entrySelectedIndex]->toggleSelection();
        if (this->entries[entrySelectedIndex + 1] != nullptr)
        {
            this->entries[entrySelectedIndex + 1]->toggleSelection();
        }
    }
}

void SettingsListArea::onUp(int currentSelectedIndex)
{
    this->console->println("On button up");
    if (currentSelectedIndex == -1)
    {
        this->entries[0]->select();
        displayEntries();
        this->console->println("Select the first and show");
        return;
    }
    int entrySelectedIndex = currentSelectedIndex;
    if (entrySelectedIndex > 0)
    {
        this->console->println("Button pressed and toggle selection");
        this->entries[entrySelectedIndex]->toggleSelection();
        if (this->entries[entrySelectedIndex - 1] != nullptr)
        {
            this->entries[entrySelectedIndex - 1]->toggleSelection();
        }
    }
    else
    {
        this->entries[entrySelectedIndex]->toggleSelection();
    }
}
