#ifndef FLASHMETER_MODEL_H
#define FLASHMETER_MODEL_H

#include <Arduino.h>
#include "entry.h"
 

class Observer;

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

    String currentFocale;
  
    
    
    //double currentEVValue;

    Entry* modeEntry;
    Entry* sensitivityEntry;
  
    Observer* observer;
  
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

    String getCurrentFocale() const {return currentFocale;};

    void setCurrentFocale(double focale);

    int getCurrentMode();
    void setCurrentMode(int mode);
    Entry* getEntry(int index);
    int getEntriesCount(){ return 2;}

    bool save();

    void setAttachCallback( void (*attach)());
    void setDetachCallback( void (*detach)());

    void registerObserver(Observer* observer);
    
};

#endif //FLASHMETER_MODEL_H