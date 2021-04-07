#include "esp_eeprom_repository.h"
#include <EEPROM.h>

EspEEPROMRepository::EspEEPROMRepository(void (*attach)(), void (*detach)())
{
    EEPROM.begin(512);
    this->attachInterruptCallback = attach;
    this->detachInterruptCallback = detach;
    
}

int EspEEPROMRepository::loadKey(const int key) 
{
    int value;
    this->detachInterruptCallback();
    
    value = EEPROM.readInt( key );
    this->attachInterruptCallback();
    Serial.print("Load key: ");
    Serial.print(key);
    Serial.print(" : ");
    Serial.println(value);
    return value;
}

void EspEEPROMRepository::saveKey( const int key, int value)
{

    Serial.print("Saving key ");
    Serial.print(key);
    Serial.print(" : ");
    Serial.println(value);
    //Detach interruption to allow use of the memory
    this->detachInterruptCallback();

    // int address = MODE_INDEX;

    EEPROM.writeInt(key,value);
    EEPROM.commit();
   

    this->attachInterruptCallback();

    //Refresh the values on the model
    //this->setSensitivityFromIndex();
     
}

/* repository->saveKey("SENSITIVITY", this->sensitivityIndex);
        repository->saveKey("APERTURE", this->preferredApertureIndex);
        repository->saveKey("MODE", this->modeIndex);
        */

