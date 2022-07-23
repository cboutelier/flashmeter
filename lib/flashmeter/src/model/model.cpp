#include "model.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Model::Model(Repository *repo, TimerService *timerService)
{
    this->repository = repo;
    this->timer = timerService;
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

    flashDelayEntry = new Entry(2, 2);
    flashDelayEntry->setEntryName("Delay");
    flashDelayEntry->addValue("5");
    flashDelayEntry->addValue("10");
    flashDelayEntry->addValue("20");
    flashDelayEntry->addValue("30");
    flashDelayEntry->addValue("60");
    flashDelayEntry->setCallback(Model::onValidateSettingCallback, this);

    this->currentLuxValue = 0.0;
    this->timeout = 0;

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
    else if (key == 2)
    {
        self->setFlashDelayIndex(value);
    }
    self->save();

    // self->onValidateSetting( value);
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

void Model::setFlashDelayIndex(const int newIndex)
{
    if (newIndex >= 0)
    {
        this->flashDelayIndex = newIndex;
        this->flashDelay = atoi(flashDelayEntry->getValues()[newIndex]);
        this->flashDelayEntry->setCurrentValueIndex(newIndex);
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
        this->flashDelayIndex = repository->loadKey(FLASH_DELAY_KEY);

        setSensitivityIndex(sensIndex);
        getModeEntry()->setCurrentValueIndex(this->modeIndex);
        getSensitivityEntry()->setCurrentValueIndex(sensIndex);
        getFlashDelayEntry()->setCurrentValueIndex(this->flashDelayIndex);
        setFlashDelayIndex(this->flashDelayIndex);
    }
}

void Model::save()
{
    if (this->repository != nullptr)
    {
        repository->saveKey(SENSITIVITY_KEY, this->sensitivityIndex);
        repository->saveKey(APERTURE_KEY, this->preferredApertureIndex);
        repository->saveKey(MODE_KEY, this->modeIndex);
        repository->saveKey(FLASH_DELAY_KEY, this->flashDelayIndex);
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

double Model::getProgress()
{
    return this->progress;
}

int Model::getTimeCounter()
{
    return this->timeCounter;
}

void Model::tick()
{
    this->timeCounter++;

    if (timeCounter > flashDelay)
    {
        this->timer->disableAlarm();
        this->timeout = 1;
        this->readingOn = false;
    }
    else
    {
        this->timeout = 0;
        this->progress = (double)this->timeCounter / ((double)this->flashDelay);
    }
    this->fireEvents();
}

void Model::onTimerStart()
{
}

void Model::startStrobeTimer()
{
    this->timeCounter = 0;
    this->progress = -1;
    this->timeout = 0;
    // this->tick();
    if (this->timer != nullptr)
    {
        this->timer->enableAlarm();
        this->readingOn = true;
    }
}

bool Model::shouldRead(){
    return this->readingOn;
}

void Model::strobeDetected(){
     this->readingOn = false;
      this->timer->disableAlarm();
}