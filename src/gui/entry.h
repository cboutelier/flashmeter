#ifndef ENTRY_H
#define ENTRY_H

#include <Arduino.h>

class Entry
{

public:
    Entry();
    Entry(const int &yOffset);
    void setOffset(const int &yOffset);
    
    int getCurrentValueIndex() { return currentValueIndex; }
    void setCurrentValueIndex(int indx)
    {
        this->currentValueIndex = indx;
        Serial.println("Set the value...");
    };
    /* int getHighlightedIndex(){ return this->highlightedIndex;}
    void setHightlightedIndex(const int index){ this->highlightedIndex = index;}
    */
    void setEntryName(String name) { this->entryName = name; }
    String getEntryName() { return this->entryName; }
    int getEnabledValuesCount() { return this->enabledValuesCount; }
    bool addValue(String value);
    String getValue(int index) { return this->values[index]; }
    void dump()
    {
        Serial.println("Entry: ");
        Serial.println("Name   " + entryName);
        Serial.print("Offset  ");
        Serial.println(yOffset);
        Serial.print("CVI   ");
        Serial.println(currentValueIndex);
        Serial.print("EVC   ");
        Serial.println(enabledValuesCount);
    }
    

private:
    /* Indicates the index of the current value */
    int currentValueIndex = -1;

    // int highlightedIndex = -1;

    
    int yOffset;
    String entryName;
    int enabledValuesCount = 0;
    String values[10];
};

#endif //ENTRY_H