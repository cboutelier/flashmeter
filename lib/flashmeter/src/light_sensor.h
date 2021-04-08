#pragma once

 
#include <light_sensor_device.h>
#include <model/model.h>
#include <observer.h>
#include <console_delegator.h>

class LightSensor : public Observer
{

public:
    LightSensor(LightSensorDevice *device, Model *model, ConsoleDelegator* console);
    void read();
    
    virtual void onReceiveDataFromSubject(const Observable* model);

protected:
    LightSensorDevice *device;
    Model *model;
    ConsoleDelegator* console;
    float previousLuxValue = -1.0;
    int previousLuxIntValue = -1;
    double speeds[28];
  
    int calculateSpeedIndex( int EV100, int sensibilityIndex, int focalIndex) const;
private:
    void buildSpeedArray();

};