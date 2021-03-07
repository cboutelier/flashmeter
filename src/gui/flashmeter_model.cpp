#include "flashmeter_model.h"
#include <EEPROM.h>

#define MODE_INDEX 0
#define SENSITIVITY_INDEX 1

FlashMeterModel::FlashMeterModel()
{

    Serial.println("------------- Constructor of FlashMeterModel ----------------");
    modeEntry = new Entry(0);
    modeEntry->setEntryName("Mode");
    modeEntry->addValue("Ambient");
    modeEntry->addValue("Flash");

    // modeEntry->setCurrentValueIndex(1);

    sensitivityEntry = new Entry(1);
    sensitivityEntry->setEntryName("Sensitivity");
    sensitivityEntry->addValue("100");
    sensitivityEntry->addValue("200");
    sensitivityEntry->addValue("400");
    /*  sensitivityEntry->addValue("800");
    sensitivityEntry->addValue("1600");*/
    // sensitivityEntry->setCurrentValueIndex(2);
    loadFromEEPROM();
}

void FlashMeterModel::loadFromEEPROM()
{
    modeEntry->setCurrentValueIndex(EEPROM.readInt(MODE_INDEX));
    sensitivityEntry->setCurrentValueIndex(EEPROM.readInt(MODE_INDEX + sizeof(int)));
}

bool FlashMeterModel::save()
{
    //Detach interruption to allow use of the memory 
     this->detachInterruptCallback();
 
    int address = MODE_INDEX;
   

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
    return commit;
}

Entry *FlashMeterModel::getEntry(int index)
{
    switch (index)
    {

    case 0:
        return this->modeEntry;
    case 1:
        return this->sensitivityEntry;
    default:
        Serial.println("No such element");
        return NULL;
    }
}

int FlashMeterModel::getCurrentMode()
{
    return this->currentMode;
}

void FlashMeterModel::setCurrentMode(int modeIndex)
{
    this->currentMode = modeIndex;
}

long FlashMeterModel::getCurrentLuxValue()
{
    return this->currentLuxValue;
}

void FlashMeterModel::setCurrentLuxValue(long luxValue)
{
    this->currentLuxValue = luxValue;
}


void FlashMeterModel::setAttachCallback( void (*attach)()){
    this->attachInterruptCallback = attach;
}

void FlashMeterModel::setDetachCallback( void (*detach)()){
        this->detachInterruptCallback = detach;
}