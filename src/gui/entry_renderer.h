#ifndef ENTRY_RENDERER_H
#define ENTRY_RENDERER_H

#include <Arduino.h>
#include "entry.h"
#include <TFT_eSPI.h>

class EntryRenderer
{

private:
    Entry *entry;

    int yOffset;

    TFT_eSPI *display;
    unsigned short background_color;
    unsigned short foreground_color;
    unsigned short selected_color;

    bool entrySelected = false;

    unsigned short highlightedIndex = -1;
    /* index of the value being 'selected'  */
    int valueSelectedIndex = -1;

    // void (*onSelect)();

public:
    EntryRenderer();
    EntryRenderer(TFT_eSPI *display, Entry *entry, int yOffset);
    void show();
    void init(TFT_eSPI *display, Entry *entry, int yOffset);
    void setInitialColors(unsigned short background, unsigned short foreground, unsigned short selected);
    void setHighlightedIndex(unsigned short index) { this->highlightedIndex = index; }
    unsigned short getHighlightedIndex()
    {
        return this->highlightedIndex;
    }
    void setEntrySelected(const bool selected) { this->entrySelected = selected; }
    bool isEntrySelected() { return entrySelected; }

    
    void onRight();
    void onLeft();
    bool onOk();

    // void setOnSelect(void (*func)());
};

#endif //ENTRY_RENDERER_H