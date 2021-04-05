#ifndef ENTRY_H
#define ENTRY_H

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
    };

    void setEntryName(const char *name);
    const char *getEntryName();
    int getEnabledValuesCount() { return this->enabledValuesCount; }
    bool addValue(const char *value);
    const char *getValue(int index) { return this->values[index]; }
    bool isSelected() const { return this->selected; };
    void toggleSelection() { this->selected = !this->selected; };
    void select() { this->selected = true; }

private:
    /* Indicates the index of the current value */
    int currentValueIndex = -1;

    int yOffset;
    char entryName[50];
    int enabledValuesCount = 0;
    char values[10][20];
    bool selected = false;
};

#endif //ENTRY_H