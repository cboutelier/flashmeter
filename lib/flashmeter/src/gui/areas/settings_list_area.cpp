#include "settings_list_area.h"
#include "../../model/model.h"

#include <stdio.h>
#include <string.h>
#include "renderers/entry_renderer.h"
#include "entry_area.h"

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
    Model* model = (Model*)observable;

    char *msg = new char[50];
    sprintf(msg, "version %i", model->getConfigurationVersion());
   // this->console->println(msg);

    if( this->configurationVersion != model->getConfigurationVersion()){
        this->console->println("Received event on setting list");
        this->configurationVersion = model->getConfigurationVersion();
        this->show();
    }
    delete [] msg;
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
    bool repaint = false;
    int entrySelectedIndex = -1;
    for (int i = 0; i < entryCount; i++)
    {
        if (this->entries[i] != nullptr && this->entries[i]->isSelected())
        {
            entrySelectedIndex = i;
            break;
        }
    }

    char msg[50];
    sprintf(msg, "Selected %i", entrySelectedIndex);
    this->console->println(msg);

    if (button == 1)
    {
        
        repaint = onUp(entrySelectedIndex);
    }
    else if (button == 2)
    {
        
        repaint = onDown(entrySelectedIndex);
    }
    else if (button == 3)
    {
        //LEFT
    }
    else if (button == 4)
    {
        //RIGHT
    }
    else if (button == 6)
    {
        //OK
        if (entrySelectedIndex >= 0)
        {
            Entry *entry = this->entries[entrySelectedIndex];
            if (!entry->isEdited())
            {
                entry->setEdited(true);
                choiceArea = new EntryArea(this->display, this->console, 10, 0, 210, 135);
                choiceArea->setForeground(TFT_BLACK);
                choiceArea->setBackground(TFT_RED);
                choiceArea->setOkCallback(SettingsListArea::onValidateSettingCallback, this);
                choiceArea->setEntryIndex(entrySelectedIndex);
                choiceArea->setValues(entry->getValues(), entry->getEnabledValuesCount());
                choiceArea->setCurrentIndex(entry->getCurrentValueIndex());
                choiceArea->show();
            }
            else
            {
                if (choiceArea != nullptr)
                {
                    choiceArea->onOk();
                }
            }
        }
    }
    if (repaint)
    {
        displayEntries();
    }
}

bool SettingsListArea::onDown(int currentSelectedIndex)
{
    this->console->println("On button down");

    if (currentSelectedIndex == -1)
    {
        this->entries[0]->select();
        displayEntries();
        this->console->println("Select the first and show");
        return true;
    }
    int entrySelectedIndex = currentSelectedIndex;

    if (this->entries[entrySelectedIndex]->isEdited())
    {
        choiceArea->onDown();
        return false;
    }
    else
    {

        if (entrySelectedIndex < (entryCount - 1))
        {
            this->console->println("Button pressed and toggle selection");
            this->entries[entrySelectedIndex]->toggleSelection();
            if (this->entries[entrySelectedIndex + 1] != nullptr)
            {
                this->entries[entrySelectedIndex + 1]->toggleSelection();
            }
        }
        return true;
    }
}

bool SettingsListArea::onUp(int currentSelectedIndex)
{
    this->console->println("On button up");
    if (currentSelectedIndex == -1)
    {
        this->entries[0]->select();
        displayEntries();
        this->console->println("Select the first and show");
        return true;
    }
    int entrySelectedIndex = currentSelectedIndex;

    if (this->entries[entrySelectedIndex]->isEdited())
    {
        choiceArea->onUp();
        return false;
    }
    else
    {
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
        return true;
    }
}

void SettingsListArea::onValidateSettingCallback(int value, void *this_pointer)
{
    SettingsListArea *self = static_cast<SettingsListArea *>(this_pointer);
    self->onValidateSetting(value);
    
}

void SettingsListArea::onValidateSetting(int value)
{
    this->console->println("onValidate settings");
    if (this->choiceArea != nullptr)
    {
        delete choiceArea;
    }
    for (int i = 0; i < entryCount; i++)
    {
        if (this->entries[i] != nullptr && this->entries[i]->isSelected())
        {
            this->entries[i]->onOk(value);
            this->entries[i]->setEdited(false);
            break;
        }
    }
    this->refreshPageCallback(this->page);
}
