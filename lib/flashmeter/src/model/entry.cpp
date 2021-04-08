#include "entry.h"
#include <stdio.h>
#include <string.h>

Entry::Entry(const int &yOffset, int keyNum)
{

    this->yOffset = yOffset;
    this->keyNum = keyNum;
    this->v = new char*[10];
}

Entry::Entry()
{
}

Entry::~Entry(){
    for( int j= 0 ; j<10; j++) {
        if( v[j] != nullptr){
            delete [] v[j];
        }
    }
    delete [] v;
}

void Entry::setOffset(const int &yOffset)
{
    this->yOffset = yOffset;
}

void Entry::setEntryName(const char *name)
{
    strcpy(entryName, name);
}
const char *Entry::getEntryName()
{
    return entryName;
};

bool Entry::addValue(const char *newValue)
{
    if (this->enabledValuesCount < 10)
    {
        strcpy(this->values[this->enabledValuesCount], newValue);
        this->v[this->enabledValuesCount] = new char[ strlen(newValue)];
        strcpy(v[this->enabledValuesCount], newValue);
        this->enabledValuesCount++;
        return true;
    }
    return false;
}