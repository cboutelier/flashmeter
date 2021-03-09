#include "flashmeter_model.h"
#include <EEPROM.h>
#include "observer.h"

#define MODE_INDEX 0
#define SENSITIVITY_INDEX 1

FlashMeterModel::FlashMeterModel()
{

    for( int j = 0; j < MAX_REGISTERED_OBSERVERS; j++){
         this->observers[j] = NULL;
    }

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

long FlashMeterModel::getCurrentLuxValue() const
{
    return this->currentLuxValue;
}

void FlashMeterModel::setCurrentLuxValue(long luxValue)
{
    this->currentLuxValue = luxValue;
    for (int j = 0; j < this->registeredObservers; j++)
    {
        this->observers[j]->onReceiveDataFromSubject(this);
    }
}

void FlashMeterModel::setAttachCallback(void (*attach)())
{
    this->attachInterruptCallback = attach;
}

void FlashMeterModel::setDetachCallback(void (*detach)())
{
    this->detachInterruptCallback = detach;
}

void FlashMeterModel::registerObserver(Observer *observer)
{
    if (this->registeredObservers < MAX_REGISTERED_OBSERVERS)
    {
        for( int j = 0; j < MAX_REGISTERED_OBSERVERS; j++){
            Serial.println("Try to register");
            
            if( this->observers[j] == NULL){
                Serial.println(" FOUND ONE");
                this->observers[j] = observer;
                this->registeredObservers++;
                Serial.println("register observer");
                break;
            }
            Serial.println("Did not make it");
        
        }
        
    }
}

void FlashMeterModel::unRegisterObserver(Observer *observer)
{
    if (this->registeredObservers == 0){
        return;
    } 
    for( int j = 0; j < MAX_REGISTERED_OBSERVERS; j++)
    {
        if( this->observers[j] == observer) {
            this->observers[j] = nullptr;
            this->registeredObservers++;
            break;
        }
        
        Serial.println("unregister observer");
    }
}

void FlashMeterModel::setCurrentFocale(double focale)
{
    this->currentFocale = String(focale);
    for (int j = 0; j < this->registeredObservers; j++)
    {
        this->observers[j]->onReceiveDataFromSubject(this);
    }
}

 