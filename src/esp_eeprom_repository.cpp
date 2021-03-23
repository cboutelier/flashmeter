#include "esp_eeprom_repository.h"
#include <EEPROM.h>

EspEEPROMRepository::EspEEPROMRepository(void (*attach)(), void (*detach)())
{
    EEPROM.begin(512);
    this->attachInterruptCallback = attach;
    this->detachInterruptCallback = detach;
}

int EspEEPROMRepository::loadKey(const char *key) const
{
    return 0;
}

void EspEEPROMRepository::saveKey(const char *key, int value)
{
    //Detach interruption to allow use of the memory
    this->detachInterruptCallback();

   /* int address = MODE_INDEX;

    EEPROM.writeInt(address, modeEntry->getCurrentValueIndex());
    EEPROM.writeInt(address + sizeof(int), sensitivityEntry->getCurrentValueIndex());

    bool commit = EEPROM.commit();
    if (commit)
    {
        Serial.println("Could commit");
    }
    else
    {
        Serial.println("Couldnt commit");
    }

    this->attachInterruptCallback();

    //Refresh the values on the model
    this->setSensitivityFromIndex();
    */
}
