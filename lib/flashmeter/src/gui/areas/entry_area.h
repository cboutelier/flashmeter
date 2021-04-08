#ifndef ENTRY_AREA_H
#define ENTRY_AREA_H

#include "area.h"
#include "../../console_delegator.h"

class EntryArea : public Area
{

public:
    EntryArea(DisplayDevice *d, ConsoleDelegator *console, int x, int y, int width, int height);
    virtual ~EntryArea();
    void show();
    void fillArea();
    void onReceiveDataFromSubject(const Observable *model);
    void setCurrentIndex( const int index){ this->currentIndex = index;};

    int getEntryIndex() const { return entryIndex; };
    void setEntryIndex(const int entryIndex) { this->entryIndex = entryIndex; };
     

    void setValues(char **v, int valueSize)
    {
        this->values = v;
        this->valuesCount = valueSize;
    };

    void onOk();
    void onDown();
    void onUp();
    void setOkCallback(void (*callback)(int value, void *o), void *settings)
    {
        this->callback = callback;
        settingsArea = settings;
    };

private:
    void *settingsArea;
    void (*callback)(int value, void *o);
    ConsoleDelegator *console;

    int currentIndex = 0;
 

    /**
     * index of the setting
     **/
    int entryIndex = -1;
    int valuesCount = 0;
    char **values;
};

#endif //ENTRY_AREA_H