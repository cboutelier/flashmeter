#ifndef LIGHT_SENSOR_DEVICE
#define LIGHT_SENSOR_DEVICE


class LightSensorDevice
{

public:
   // void begin(int resolution);
    virtual float readLightLevel() = 0;
};

#endif // LIGHT_SENSOR_DEVICE