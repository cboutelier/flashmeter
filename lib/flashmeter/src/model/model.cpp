#include "model.h"

Model::Model(Repository *repo)
{
    this->repository = repo;
    for (int j = 0; j < MAX_REGISTERED_OBSERVERS; j++)
    {
        this->observers[j] = nullptr;
    }

    /*modeEntry = new Entry(0);
    modeEntry->setEntryName("Mode");
    modeEntry->addValue("Ambient");
    modeEntry->addValue("Flash");

     
    sensitivityEntry = new Entry(1);
    sensitivityEntry->setEntryName("Sensitivity");
    sensitivityEntry->addValue("100");
    sensitivityEntry->addValue("200");
    sensitivityEntry->addValue("400");
     ensitivityEntry->addValue("800");
    sensitivityEntry->addValue("1600"); 
    */

    this->currentLuxValue = 0.0;

    load();
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

int Model::getSpeedIndex() const
{
    return this->speedIndex;
}

int Model::getSensitivityIndex() const
{
    return this->sensitivityIndex;
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

void Model::load()
{
    if (this->repository != nullptr)
    {
        this->sensitivityIndex = repository->loadKey("SENSITIVITY");
        this->preferredApertureIndex = repository->loadKey("APERTURE");
        this->modeIndex = repository->loadKey("MODE");
    }
}

void Model::save()
{
    if (this->repository != nullptr)
    {
        repository->saveKey("SENSITIVITY", this->sensitivityIndex);
        repository->saveKey("APERTURE", this->preferredApertureIndex);
        repository->saveKey("MODE", this->modeIndex);
    }
}

void Model::savePreferedAperture()
{
    if (this->repository != nullptr)
    {
        repository->saveKey("APERTURE", this->preferredApertureIndex);
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