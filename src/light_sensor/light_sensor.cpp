#include "light_sensor.h"

LightSensor::LightSensor(BH1750 *device, FlashMeterModel *model)
{
    this->device = device;
    this->model = model;
    this->device->begin(BH1750::CONTINUOUS_LOW_RES_MODE);
    this->buildSpeedArray();
}

void LightSensor::onReceiveDataFromSubject(const FlashMeterModel *model)
{
    this->previousLuxValue = -1;
}

void LightSensor::read()
{

    //get the value of the sensor
    float lux = this->device->readLightLevel();
    if (lux != this->previousLuxValue)
    {
        this->model->setCurrentLuxValue(lux);
        this->previousLuxValue = lux;
        int currentEV100 = (log10(lux) - log10(2.5)) / log10(2);
        int currentEVAtSensitivity = currentEV100 + this->model->getSensitivityIndex();
        if (currentEVAtSensitivity > 0 && currentEVAtSensitivity <= 20)
        {
            this->model->setSpeed(this->speeds[this->model->getPreferredApertureIndex()][currentEVAtSensitivity]);
        }
        else
        {
            this->model->setSpeed(0.0);
        }
    }
}

void LightSensor::buildSpeedArray()
{

    this->speeds[0][0] = 2.0;
    this->speeds[0][1] = 1.0;
    this->speeds[0][2] = 1 / 2.0;
    this->speeds[0][3] = 1 / 4.0;
    this->speeds[0][4] = 1 / 8.0;
    this->speeds[0][5] = 1 / 15.0;
    this->speeds[0][6] = 1 / 30.0;
    this->speeds[0][7] = 1 / 60.0;
    this->speeds[0][8] = 1 / 125.0;
    this->speeds[0][9] = 1 / 250.0;
    this->speeds[0][10] = 1 / 500.0;
    this->speeds[0][11] = 1 / 1000.0;
    this->speeds[0][12] = 1 / 2000.0;
    this->speeds[0][13] = 1 / 4000.0;
    this->speeds[0][14] = 1 / 8000.0;
    this->speeds[0][15] = 0;
    this->speeds[0][16] = 0;
    this->speeds[0][17] = 0;
    this->speeds[0][18] = 0;
    this->speeds[0][19] = 0;
    this->speeds[0][20] = 0;

    this->speeds[1][0] = 4.0;
    this->speeds[1][1] = 2.0;
    this->speeds[1][2] = 1.0;
    this->speeds[1][3] = 1 / 2.0;
    this->speeds[1][4] = 1 / 4.0;
    this->speeds[1][5] = 1 / 8.0;
    this->speeds[1][6] = 1 / 15.0;
    this->speeds[1][7] = 1 / 30.0;
    this->speeds[1][8] = 1 / 60.0;
    this->speeds[1][9] = 1 / 125.0;
    this->speeds[1][10] = 1 / 250.0;
    this->speeds[1][11] = 1 / 500.0;
    this->speeds[1][12] = 1 / 1000.0;
    this->speeds[1][13] = 1 / 2000.0;
    this->speeds[1][14] = 1 / 4000.0;
    this->speeds[1][15] = 1 / 8000.0;
    this->speeds[1][16] = 0;
    this->speeds[1][17] = 0;
    this->speeds[1][18] = 0;
    this->speeds[1][19] = 0;
    this->speeds[1][20] = 0;

    this->speeds[2][0] = 8.0;
    this->speeds[2][1] = 4.0;
    this->speeds[2][2] = 2.0;
    this->speeds[2][3] = 1.0;
    this->speeds[2][4] = 1 / 2.0;
    this->speeds[2][5] = 1 / 4.0;
    this->speeds[2][6] = 1 / 8.0;
    this->speeds[2][7] = 1 / 15.0;
    this->speeds[2][8] = 1 / 30.0;
    this->speeds[2][9] = 1 / 60.0;
    this->speeds[2][10] = 1 / 125.0;
    this->speeds[2][11] = 1 / 250.0;
    this->speeds[2][12] = 1 / 500.0;
    this->speeds[2][13] = 1 / 1000.0;
    this->speeds[2][14] = 1 / 2000.0;
    this->speeds[2][15] = 1 / 4000.0;
    this->speeds[2][16] = 1 / 8000.0;
    this->speeds[2][17] = 0;
    this->speeds[2][18] = 0;
    this->speeds[2][19] = 0;
    this->speeds[2][20] = 0;

    this->speeds[3][0] = 15.0;
    this->speeds[3][1] = 8.0;
    this->speeds[3][2] = 4.0;
    this->speeds[3][3] = 2.0;
    this->speeds[3][4] = 1.0;
    this->speeds[3][5] = 1 / 2.0;
    this->speeds[3][6] = 1 / 4.0;
    this->speeds[3][7] = 1 / 8.0;
    this->speeds[3][8] = 1 / 15.0;
    this->speeds[3][9] = 1 / 30.0;
    this->speeds[3][10] = 1 / 60.0;
    this->speeds[3][11] = 1 / 125.0;
    this->speeds[3][12] = 1 / 250.0;
    this->speeds[3][13] = 1 / 500.0;
    this->speeds[3][14] = 1 / 1000.0;
    this->speeds[3][15] = 1 / 2000.0;
    this->speeds[3][16] = 1 / 4000.0;
    this->speeds[3][17] = 0;
    this->speeds[3][18] = 0;
    this->speeds[3][19] = 0;
    this->speeds[3][20] = 0;

    this->speeds[4][0] = 30.0;
    this->speeds[4][1] = 15.0;
    this->speeds[4][2] = 8.0;
    this->speeds[4][3] = 4.0;
    this->speeds[4][4] = 2.0;
    this->speeds[4][5] = 1.0;
    this->speeds[4][6] = 1 / 2.0;
    this->speeds[4][7] = 1 / 4.0;
    this->speeds[4][8] = 1 / 8.0;
    this->speeds[4][9] = 1 / 15.0;
    this->speeds[4][10] = 1 / 30.0;
    this->speeds[4][11] = 1 / 60.0;
    this->speeds[4][12] = 1 / 125.0;
    this->speeds[4][13] = 1 / 250.0;
    this->speeds[4][14] = 1 / 500.0;
    this->speeds[4][15] = 1 / 1000.0;
    this->speeds[4][16] = 1 / 2000.0;
    this->speeds[4][17] = 1 / 4000.0;
    this->speeds[4][18] = 0;
    this->speeds[4][19] = 0;
    this->speeds[4][20] = 0;
}