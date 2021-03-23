#pragma once

 
#include <light_sensor_device.h>
#include <model/model.h>
#include <observer.h>

class LightSensor : public Observer
{

public:
    LightSensor(LightSensorDevice *device, Model *model);
    void read();
    
    virtual void onReceiveDataFromSubject(const Model* model);

protected:
    LightSensorDevice *device;
    Model *model;
    float previousLuxValue = -1.0;
    double speeds[28];

    int calculateSpeedIndex( int EV100, int sensibilityIndex, int focalIndex) const;
private:
    void buildSpeedArray();

};