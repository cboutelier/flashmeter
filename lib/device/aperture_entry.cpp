#include "aperture_entry.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

ApertureEntry::ApertureEntry(char *display, const double simplified, const double value)
{
    this->mDisplay= new char[strlen(display)+1];
    sprintf(this->mDisplay, display);
    this->mSimplified = simplified;
    this->mValue = value;
    
}

ApertureEntry::ApertureEntry()
{
}
ApertureEntry::~ApertureEntry(){
    delete this->mDisplay;
}