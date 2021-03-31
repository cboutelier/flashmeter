#include "esp_eeprom_repository.h"
#include <EEPROM.h>

EspEEPROMRepository::EspEEPROMRepository(void (*attach)(), void (*detach)())
{
    EEPROM.begin(512);
    this->attachInterruptCallback = attach;
    this->detachInterruptCallback = detach;
    
}

int EspEEPROMRepository::loadKey(char const *key) 
{
    int value;
    this->detachInterruptCallback();
    int address = getAddress(key);
    value = EEPROM.readInt( address );
    this->attachInterruptCallback();
    return value;
}

void EspEEPROMRepository::saveKey( char  const *key, int value)
{
    //Detach interruption to allow use of the memory
    this->detachInterruptCallback();

    // int address = MODE_INDEX;

    EEPROM.writeInt(getAddress(key),value);
    EEPROM.commit();
   

    this->attachInterruptCallback();

    //Refresh the values on the model
    //this->setSensitivityFromIndex();
     
}

/* repository->saveKey("SENSITIVITY", this->sensitivityIndex);
        repository->saveKey("APERTURE", this->preferredApertureIndex);
        repository->saveKey("MODE", this->modeIndex);
        */

int EspEEPROMRepository::getAddress(char const *key){
    if( strcmp( key, "APERTURE") == 0){
        return 0 + 2*sizeof(int);
    }
    return 0;
}