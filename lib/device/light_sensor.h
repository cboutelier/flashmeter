#pragma once

#include "verbose.h"
#include "light_sensor_device.h"
#include "light_reading_result.h"

class LightSensor : public Verbose
{

public:
    LightSensor(LightSensorDevice *device, ConsoleDelegator *console, int mode);
    LightReadingResult* read();
    void setMode(int mode){ currentMode = mode;};
    

protected:
    LightSensorDevice *device;
    void initSensor(){};
    
    int calculateSpeedIndex(int EV100, int sensibilityIndex, int focalIndex) const;

    float previousLuxValue = -1.0;
    int previousLuxIntValue = -1;
    double speeds[28];
    int currentMode = 0;

    

private:
    void buildSpeedArray();
};