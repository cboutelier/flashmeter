#ifndef FMM_H
#define FMM_H

#include <observable.h>
#include <repository.h>
#include "entry.h"

#define MAX_SENSITIVITY_INDEX 10

/**
 * Supported ISO values: 2^n  (100/200/400/800)
 **/
class Model : public Observable
{

public:
    Model(Repository *repo);
    void setCurrentLuxValue(float luxValue, bool fireEvent);
    double getCurrentLuxValue() const { return this->currentLuxValue; };
    //DEPRECATED
    void setSpeed(const double speed, bool fireEvent);
    void setSpeedIndex(const int speedIndex, bool fireEvent);

    int getSensitivityIndex() const;
    void setSensitivityIndex(const int newIndex);
    const char *getSensitivityValue() const;
    int getPreferredApertureIndex() const;
    int getSpeedIndex() const;
    void setCurrentEV(const int ev) { this->currentEV = ev; };
    int getCurrentEV() const { return this->currentEV; };

    virtual void registerObserver(Observer *observer);
    virtual void unRegisterObserver(Observer *observer);

    void increaseApertureIndex();
    void decreaseApertureIndex();

    Entry *getModeEntry() { return this->modeEntry; };
    Entry *getSensitivityEntry(){ return this->sensitivityEntry;};

private:
    Repository *repository;

    float currentLuxValue;

    int sensitivity;

    int preferredApertureIndex = 0;

    int sensitivityIndex = 0;
    char sensitivityValue[20];

    int modeIndex = 0;

    double speed;

    int speedIndex = 0;

    //EV value is calculated from lux value for the current sensitivity.
    int currentEV;

    Observer *observers[MAX_REGISTERED_OBSERVERS];
    int registeredObservers = 0;

    Entry *modeEntry;
    Entry *sensitivityEntry;

    void fireEvents() const;
    void load();
    void save();
    void savePreferedAperture();
};

#endif //FMM_H