#include "entry.h"
#include <stdio.h>
#include <string.h>

Entry::Entry(const int &yOffset)
{

    this->yOffset = yOffset;
}

Entry::Entry()
{
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
        this->enabledValuesCount++;
        return true;
    }
    return false;
}