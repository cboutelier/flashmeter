#ifndef FMM_H
#define FMM_H

#include <observable.h>
#include <repository.h>

class Model : public Observable
{

public:
    Model(Repository* repo);
    void setCurrentLuxValue(float luxValue, bool fireEvent);
    void setSpeed(const double speed, bool fireEvent);

    int getSensitivityIndex() const;
    int getPreferredApertureIndex() const;

    virtual void registerObserver(Observer *observer);
    virtual void unRegisterObserver(Observer *observer);

private:

    Repository* repository;

    float currentLuxValue;

    int sensitivity;

    int preferredApertureIndex = 0;

    int sensitivityIndex = 0;

    int modeIndex = 0;

    double speed;

    //EV value is calculated from lux value for the current sensitivity.
    int currentEV;

    Observer *observers[MAX_REGISTERED_OBSERVERS];
    int registeredObservers = 0;

    void fireEvents() const;
    void load();
    void save();
};

#endif //FMM_H