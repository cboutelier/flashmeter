#include "entries_array.h"

//#include <memory.h>
#include <assert.h>

EntriesArray::EntriesArray(long size)
{

    assert(size > 0);
    mypArray = new Entry[size];
    if (mypArray == 0)
    {
        Serial.println(F("Could not allocate memory"));
        return;
    }
    mySize = size;
}

EntriesArray &EntriesArray::operator=(const EntriesArray &a)
{
    this->clear();
    mypArray = new Entry[a.mySize];
    if (mypArray == 0)
    {
        Serial.println("Could not allocate memory for operator =");
    }
    mySize = a.mySize;
    memcpy(mypArray, a.mypArray, mySize * sizeof(Entry));
    return *this;
}

bool EntriesArray::add(const Entry &entry)
{
    Entry *pTemp = new Entry[++mySize];
    if (pTemp == 0)
    {
        Serial.println(F("Could not allocate memory for add"));
        --mySize;
        return false;
    }
    if (mypArray)
    {
        memcpy(pTemp, mypArray, mySize * sizeof(Entry));
    }

    pTemp[mySize - 1] = entry;

    if (mypArray)
    {
        delete[] mypArray;
    }
    mypArray = pTemp;
    return true;
}

void EntriesArray::clear(){
    if( mypArray){
        delete[] mypArray;
        mypArray = 0;
        mySize = 0;
    }
}

bool EntriesArray::remove( const int& index){
    Entry *pTemp = new Entry[--mySize];
    if( pTemp == 0){
        Serial.println(F("Could not remove"));
        mySize++;
        return false;
    }
    if ( mypArray){
        memcpy(pTemp, mypArray, index * sizeof(Entry));
        memcpy(pTemp+index, &mypArray[index+1], (mySize-index)*sizeof(Entry));
        delete[] mypArray;
    }

    mypArray = pTemp;
    return true;
}