#ifndef __ENTRIES_ARRAY_H__
#define __ENTRIES_ARRAY_H__

#include <Arduino.h>
#include "entry.h"

class EntriesArray
{

public:
    EntriesArray() : mypArray(0), mySize(0) {}
    EntriesArray(long size);
    virtual ~EntriesArray() { this->clear(); };

    bool add(const Entry &entry);
    void clear();
    bool remove(const int &index);
    int size() const { return mySize; }
    EntriesArray& operator=(const EntriesArray &a);
    Entry &operator[](const int &index) { return mypArray[index]; }

protected:
    Entry *mypArray;
    int mySize;
};

#endif //__ENTRIES_ARRAY_H__