#ifndef ENTRY_RENDERER_H
#define ENTRY_RENDERER_H

 
#include "../../../model/entry.h"
#include "../../../display/display_device.h"
 

class EntryRenderer
{

private:
    Entry *entry;

    /**
     * Index of the entry in the list of entries.
     **/
    int index;

    DisplayDevice *display;
    unsigned int background_color;
    unsigned int foreground_color;
    unsigned int selected_color;

    int areaBaseX;
    int areaBaseY;

    /**
     * Indicates that this specific entry is being selected for update.
     **/
    bool entrySelected = false;

    /**
     * Callback used to save the value when ok is pressed while editing a value. Must point to a method in charge of saving the value in the model.
     **/
    //void (*onOkCallBack)(char const *key, int index);

public:
   
    EntryRenderer(DisplayDevice *display, Entry *entry, int areaBaseX, int areaBaseY, int index);
    void show();
  
    void setInitialColors(unsigned int background, unsigned int foreground, unsigned int selected);
    void setEntrySelected(const bool selected) { this->entrySelected = selected; }
    bool isEntrySelected() { return entrySelected; }

    
    void onRight();
    void onLeft();
    bool onOk();
};

#endif //ENTRY_RENDERER_H