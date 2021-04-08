#ifndef MOCK_LIGHT_SENSOR_H
#define MOCK_LIGHT_SENSOR_H

#include "light_sensor/generic_light_sensor_device.h"

class MockLightSensor : public GenericLightSensorDevice
{
public:
    float readLightLevel() { return 2.0f; }
};

#endif