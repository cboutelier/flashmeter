#ifndef LIGHT_SENSOR_DEVICE
#define LIGHT_SENSOR_DEVICE

#include <BH1750.h>

class LightSensorDevice : public BH1750
{

/*
public:
    enum Mode
    {
        // same as Power Down
        UNCONFIGURED = 0,
        // Measurement at 1 lux resolution. Measurement time is approx 120ms.
        CONTINUOUS_HIGH_RES_MODE = 0x10,
        // Measurement at 0.5 lux resolution. Measurement time is approx 120ms.
        CONTINUOUS_HIGH_RES_MODE_2 = 0x11,
        // Measurement at 4 lux resolution. Measurement time is approx 16ms.
        CONTINUOUS_LOW_RES_MODE = 0x13,
        // Measurement at 1 lux resolution. Measurement time is approx 120ms.
        ONE_TIME_HIGH_RES_MODE = 0x20,
        // Measurement at 0.5 lux resolution. Measurement time is approx 120ms.
        ONE_TIME_HIGH_RES_MODE_2 = 0x21,
        // Measurement at 4 lux resolution. Measurement time is approx 16ms.
        ONE_TIME_LOW_RES_MODE = 0x23
    };
    void begin(int resolution);
    float readLightLevel();*/
};

#endif //LIGHT_SENSOR_DEVICE