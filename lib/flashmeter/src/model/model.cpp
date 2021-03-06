#include "model.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

Model::Model(Repository *repo)
{
    this->repository = repo;
    for (int j = 0; j < MAX_REGISTERED_OBSERVERS; j++)
    {
        this->observers[j] = nullptr;
    }

    modeEntry = new Entry(0, 0);
    modeEntry->setEntryName("Mode");
    modeEntry->addValue("Ambient");
    modeEntry->addValue("Flash");
    modeEntry->setCallback(Model::onValidateSettingCallback, this);

    sensitivityEntry = new Entry(1, 1);
    sensitivityEntry->setEntryName("ISO");
    sensitivityEntry->addValue("100");
    sensitivityEntry->addValue("200");
    sensitivityEntry->addValue("400");
    sensitivityEntry->addValue("800");
    sensitivityEntry->addValue("1600");
    sensitivityEntry->setCallback(Model::onValidateSettingCallback, this);

    this->currentLuxValue = 0.0;

    load();
}

void Model::onValidateSettingCallback(int key, int value, void *this_pointer)
{
    Model *self = static_cast<Model *>(this_pointer);
    self->configurationVersion = self->configurationVersion + 1;

    if (key == 0)
    {
        self->setModeIndex(value);
    }
    else if (key == 1)
    {
        self->setSensitivityIndex(value);
    }
    self->save();

    //self->onValidateSetting( value);
}

void Model::setCurrentLuxValue(float luxValue, bool fireEvent)
{
    this->currentLuxValue = luxValue;
    if (fireEvent)
    {
        this->fireEvents();
    }
}
void Model::setSpeed(const double speed, bool fireEvent)
{
    this->speed = speed;
    if (fireEvent)
    {
        this->fireEvents();
    }
}

void Model::setSpeedIndex(const int speedIndex, bool fireEvent)
{
    this->speedIndex = speedIndex;
    if (fireEvent)
    {
        this->fireEvents();
    }
}

void Model::setModeIndex(const int mode)
{
    this->modeIndex = mode;
    this->modeEntry->setCurrentValueIndex(mode);
    this->fireEvents();
}

int Model::getSpeedIndex() const
{
    return this->speedIndex;
}

int Model::getSensitivityIndex() const
{
    return this->sensitivityIndex;
}

void Model::setSensitivityIndex(const int newIndex)
{
    if (newIndex >= 0 && newIndex < MAX_SENSITIVITY_INDEX)
    {
        this->sensitivityIndex = newIndex;
        int isoValue = (int)(pow(2.0, this->sensitivityIndex) * 100);
        sprintf(this->sensitivityValue, "%i", isoValue);

        this->sensitivityEntry->setCurrentValueIndex(newIndex);

        this->fireEvents();
    }
}

const char *Model::getSensitivityValue() const
{
    return this->sensitivityValue;
}

int Model::getPreferredApertureIndex() const
{
    return this->preferredApertureIndex;
}

void Model::fireEvents() const
{
    for (int j = 0; j < this->registeredObservers; j++)
    {
        this->observers[j]->onReceiveDataFromSubject(this);
    }
}

void Model::forceFireEvents() const
{
    for (int j = 0; j < this->registeredObservers; j++)
    {
        this->observers[j]->onReceiveDataFromSubject(this);
    }
}

void Model::load()
{
    if (this->repository != nullptr)
    {
        int sensIndex = repository->loadKey(SENSITIVITY_KEY);
        this->preferredApertureIndex = repository->loadKey(APERTURE_KEY);
        this->modeIndex = repository->loadKey(MODE_KEY);

        setSensitivityIndex(sensIndex);
        getModeEntry()->setCurrentValueIndex(this->modeIndex);
        getSensitivityEntry()->setCurrentValueIndex(sensIndex);
    }
}

void Model::save()
{
    if (this->repository != nullptr)
    {
        repository->saveKey(SENSITIVITY_KEY, this->sensitivityIndex);
        repository->saveKey(APERTURE_KEY, this->preferredApertureIndex);
        repository->saveKey(MODE_KEY, this->modeIndex);
    }
}

void Model::savePreferedAperture()
{
    if (this->repository != nullptr)
    {
        repository->saveKey(APERTURE_KEY, this->preferredApertureIndex);
    }
}

void Model::registerObserver(Observer *observer)
{

    if (this->registeredObservers < MAX_REGISTERED_OBSERVERS)
    {
        for (int j = 0; j < MAX_REGISTERED_OBSERVERS; j++)
        {

            if (this->observers[j] == nullptr)
            {
                this->observers[j] = observer;
                this->registeredObservers++;
                break;
            }
        }
    }
}

void Model::unRegisterObserver(Observer *observer)
{
    if (this->registeredObservers == 0)
    {
        return;
    }
    for (int j = 0; j < MAX_REGISTERED_OBSERVERS; j++)
    {
        if (this->observers[j] == observer)
        {
            this->observers[j] = nullptr;
            this->registeredObservers--;
            break;
        }
    }
}

void Model::increaseApertureIndex()
{
    if (this->preferredApertureIndex < 9)
    {
        this->preferredApertureIndex++;
        this->savePreferedAperture();
        this->fireEvents();
    }
}
void Model::decreaseApertureIndex()
{
    if (this->preferredApertureIndex > 0)
    {
        this->preferredApertureIndex--;
        this->savePreferedAperture();
        this->fireEvents();
    }
}