#include "shutter_speed_entry.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

ShutterSpeedEntry::ShutterSpeedEntry(const char *display,  const double value)
{
    this->mDisplay= new char[strlen(display)+1];
    sprintf(this->mDisplay, display);
    this->mValue = value;
    
}

ShutterSpeedEntry::ShutterSpeedEntry()
{
}
ShutterSpeedEntry::~ShutterSpeedEntry(){
    delete this->mDisplay;
}