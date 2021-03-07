#include "entry.h"

Entry::Entry( const int& yOffset)
{
  
    this->yOffset = yOffset;
}

Entry::Entry(){
    
}

void Entry::setOffset(const int& yOffset){
    this->yOffset = yOffset;
}
 
 

bool Entry::addValue(String newValue){
    if( this->enabledValuesCount < 10){
        this->values[this->enabledValuesCount] = newValue;
        this->enabledValuesCount++;
        return true;
    }
    return false;
}