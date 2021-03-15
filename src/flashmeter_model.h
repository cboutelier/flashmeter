#ifndef FLASHMETER_MODEL_H
#define FLASHMETER_MODEL_H

#include <Arduino.h>
#include "gui/entry.h"

#define MAX_REGISTERED_OBSERVERS 3

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
    float currentLuxValue;
    int sensitivity;

    String currentFocale;

    //double currentEVValue;

    Entry *modeEntry;
    Entry *sensitivityEntry;

    Observer *observers[MAX_REGISTERED_OBSERVERS];
    int registeredObservers = 0;

    void loadFromEEPROM();

    void setSensitivityFromIndex();

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
    float getCurrentLuxValue() const;
    /*  double getCurrentEVValue();
    void setCurrentSensibilityIndex();
    void setCurrentSpeedIndex();
    */
    void setCurrentLuxValue(float luxValue);
    /*   void setCurrentEVValue();*/

    String getCurrentFocale() const { return currentFocale; };

    void setCurrentFocale(double focale);

    //Sensitivy does not trigger events
    void setSensitivity(const int sensitivity) { this->sensitivity = sensitivity; }
    int getSensitivity() const { return this->sensitivity; }

    int getCurrentMode();
    void setCurrentMode(int mode);
    Entry *getEntry(int index);
    int getEntriesCount() { return 2; }

    bool save();

    void setAttachCallback(void (*attach)());
    void setDetachCallback(void (*detach)());

    void registerObserver(Observer *observer);
    void unRegisterObserver(Observer *observer);
    void fireEvents();
};

#endif //FLASHMETER_MODEL_H