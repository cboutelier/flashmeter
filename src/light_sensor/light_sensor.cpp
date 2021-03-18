#include "light_sensor.h"

LightSensor::LightSensor(BH1750 *device, FlashMeterModel *model)
{
    this->device = device;
    this->model = model;
    this->device->begin(BH1750::CONTINUOUS_LOW_RES_MODE);
}

void LightSensor::read()
{

    //get the value of the sensor
    float lux = this->device->readLightLevel();
    if (lux != this->previousLuxValue)
    {
        this->model->setCurrentLuxValue(lux);
        this->previousLuxValue = lux;
    }
}