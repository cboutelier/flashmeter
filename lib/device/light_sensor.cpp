#include <math.h>
#include <light_sensor.h>

LightSensor::LightSensor(LightSensorDevice *device, ConsoleDelegator *console, int mode)
{
    this->device = device;

    this->console = console;

    this->initSensor();
    this->setMode(mode);

    // this->device->begin(LightSensorDevice::CONTINUOUS_LOW_RES_MODE);
    this->buildSpeedArray();
}

int LightSensor::calculateSpeedIndex(int EV100, int sensibilityIndex, int apertureIndex) const
{

    // first: apply the sensitivity index
    int index = EV100 + sensibilityIndex;
    // Add the offset 9 due to the fact that array is based on f32, 9 stops
    index += 9;

    // Add aperture index for the desired aperture
    index -= apertureIndex;

    // First line is for index -1  -> index 0 = EV(-1)
    index++;
    return index;
}

LightReadingResult *LightSensor::read()
{
    float lux = this->device->readLightLevel();
    int intLux = (int)lux;
    bool success = true;
    int currentEV100 = -1;
    if (lux == 0.0f)
    {
        success = false;
    }
    else
    {
        this->previousLuxValue = lux;
        this->previousLuxIntValue = intLux;
        this->console->println("calculus");

        currentEV100 = (int)((log10(lux) - log10(2.5)) / log10(2));
    }

    // int currentEVAtSensitivity = currentEV100 + this->model->getSensitivityIndex();
    LightReadingResult *result = new LightReadingResult(this->currentMode, success, lux, currentEV100);
    return result;
}

/**
 * This array is based on the column f32, Iso 100, EV from -1 to EV21.
 */
void LightSensor::buildSpeedArray()
{
    this->speeds[0] = 60 * 32.0;
    this->speeds[1] = 60 * 16.0;
    this->speeds[2] = 60 * 8.0;
    this->speeds[3] = 60 * 4.0;
    this->speeds[4] = 60 * 2.0;
    this->speeds[5] = 60 * 1.0;
    this->speeds[6] = 30.0;
    this->speeds[7] = 15.0;
    this->speeds[8] = 8.0;
    this->speeds[9] = 4.0;
    this->speeds[10] = 2.0;
    this->speeds[11] = 1.0;
    this->speeds[12] = 1 / 2.0;
    this->speeds[13] = 1 / 4.0;
    this->speeds[14] = 1 / 8.0;
    this->speeds[15] = 1 / 15.0;
    this->speeds[16] = 1 / 30.0;
    this->speeds[17] = 1 / 60.0;
    this->speeds[18] = 1 / 125.0;
    this->speeds[19] = 1 / 250.0;
    this->speeds[20] = 1 / 500.0;
    this->speeds[21] = 1 / 1000.0;
    this->speeds[22] = 1 / 2000.0;
    this->speeds[23] = 1 / 4000.0;
    this->speeds[24] = 1 / 8000.0;
    this->speeds[25] = 1 / 16000.0;
    this->speeds[26] = 1 / 32000.0;
}