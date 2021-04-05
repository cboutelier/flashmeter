#ifndef SETTINGS_AREA_H
#define SETTINGS_AREA_H

#include "area.h"
#include "../../console_delegator.h"

class SettingsListArea : public Area
{

private:
    ConsoleDelegator *console;
    Entry** entries;

protected:
public:
    SettingsListArea(DisplayDevice *d, ConsoleDelegator *console, int x, int y, int width, int height);
    ~SettingsListArea();
    virtual void show();
    virtual void fillArea();
    virtual void onReceiveDataFromSubject(const Observable *model);
    void initEntries( const int number);
    void addEntry( Entry* entry, const int index);
    void displayEntries();
    void displayEntry(Entry* entry, int index);

};

#endif //SETTINGS_AREA_H