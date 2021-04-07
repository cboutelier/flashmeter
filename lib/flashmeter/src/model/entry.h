#ifndef ENTRY_H
#define ENTRY_H

class Entry
{

public:
    Entry();
    Entry(const int &yOffset, const int keyNum );
    ~Entry();
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
    char** getValues(){return this->v;};
    bool isSelected() const { return this->selected; };
    void toggleSelection() { this->selected = !this->selected; };
    void select() { this->selected = true; };
    bool isEdited() const { return edited; };
    void setEdited(bool e) { this->edited = e; }; 
    int getKeyNum(){return this->keyNum;};
    void setCallback( void(*c)(int key, int v, void*), void *m ){this->callback=c; this->model=m;};
    void onOk( int value ){this->callback(this->keyNum, value, model);};

private:
    /* Indicates the index of the current value */
    int currentValueIndex = -1;

    int yOffset;
    char entryName[50];
    int enabledValuesCount = 0;
    char values[10][20];
    char** v;
    bool selected = false;
    bool edited = false;

    //to link the value with the model attribute.
    int keyNum;
    void* model;
    void (*callback)(int key, int value, void* model);
   
};

#endif //ENTRY_H