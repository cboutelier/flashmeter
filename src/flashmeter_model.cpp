#include "flashmeter_model.h"
#include <EEPROM.h>
#include "gui/observer.h"

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

    this->currentLuxValue = 0.0;
    
    loadFromEEPROM();
}

void FlashMeterModel::loadFromEEPROM()
{
    modeEntry->setCurrentValueIndex(EEPROM.readInt(MODE_INDEX));
    sensitivityEntry->setCurrentValueIndex(EEPROM.readInt(MODE_INDEX + sizeof(int)));

    this->setSensitivityFromIndex();
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


    //Refresh the values on the model
    this->setSensitivityFromIndex();
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

float FlashMeterModel::getCurrentLuxValue() const
{
    return this->currentLuxValue;
}

 

void FlashMeterModel::setCurrentLuxValue(float luxValue)
{
    this->currentLuxValue = luxValue;
    this->currentEV = (log10(luxValue)-log10(2.5))/log10(2) ;
    Serial.print("EV without correction: ");
    Serial.println(this->currentEV);
    this->currentEV +=  this->sensitivityEntry->getCurrentValueIndex();
    Serial.print("EV after correction: ");
    Serial.println(this->currentEV);
    this->fireEvents();
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
            
            if( this->observers[j] == NULL){   
                this->observers[j] = observer;
                this->registeredObservers++;  
                break;
            }
           
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
            this->registeredObservers--;
            break;
        }
    }

}

void FlashMeterModel::setCurrentFocale(double focale)
{
    this->currentFocale = String(focale,1);
    this->fireEvents();
}

void FlashMeterModel::fireEvents(){
    for (int j = 0; j < this->registeredObservers; j++)
    {
        this->observers[j]->onReceiveDataFromSubject(this);
    }
}

void FlashMeterModel::setSensitivityFromIndex(){
    int currentIndex = sensitivityEntry->getCurrentValueIndex();
    int sensitivityAsInt = sensitivityEntry->getValue(currentIndex).toInt();
    this->setSensitivity(sensitivityAsInt);
}


void FlashMeterModel::setSpeed( const double speed){
    this->speed = speed;
    this->fireEvents();
}
 