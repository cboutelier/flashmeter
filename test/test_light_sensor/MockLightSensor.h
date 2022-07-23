#ifndef MOCK_LIGHT_SENSOR_H
#define MOCK_LIGHT_SENSOR_H

#include <light_sensor_device.h>

class MockLightSensor : public LightSensorDevice
{
public:
    float readLightLevel() { return mLux; }
    void setDesiredLux(float lux) { this->mLux = lux; }

private:
    float mLux;
};

#endif