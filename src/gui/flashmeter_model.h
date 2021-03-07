#ifndef FLASHMETER_MODEL_H
#define FLASHMETER_MODEL_H

#include <Arduino.h>
#include "entry.h"
#include "entries_array.h"

class FlashMeterModel
{

private:
    /*
    int currentSensibilityIndex;
    int currentSpeedIndex;
    int currentApertureIndex;
    */
    int currentMode;
    long currentLuxValue;
  
    
    
    //double currentEVValue;

    Entry* modeEntry;
    Entry* sensitivityEntry;
    void loadFromEEPROM();

protected:
    void (*attachInterruptCallback)();
    void (*detachInterruptCallback)();
    

public:
    FlashMeterModel();
    /*
    int getCurrentSensibilityIndex();
    int getCurrentSpeedIndex;
    int getCurrentApertureIndex;
    */
    long getCurrentLuxValue();
    /*  double getCurrentEVValue();
    void setCurrentSensibilityIndex();
    void setCurrentSpeedIndex();
    */
    void setCurrentLuxValue(long luxValue);
    /*   void setCurrentEVValue();*/

    int getCurrentMode();
    void setCurrentMode(int mode);
    Entry* getEntry(int index);
    int getEntriesCount(){ return 2;}

    bool save();

    void setAttachCallback( void (*attach)());
    void setDetachCallback( void (*detach)());
    
};

#endif //FLASHMETER_MODEL_H