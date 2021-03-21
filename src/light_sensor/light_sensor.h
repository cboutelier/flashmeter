#pragma once

#include <Arduino.h>
#include <BH1750.h>
#include "../flashmeter_model.h"
#include "../gui/observer.h"

class LightSensor : public Observer
{

public:
    LightSensor(BH1750 *device, FlashMeterModel *model);
    void read();
    
    virtual void onReceiveDataFromSubject(const FlashMeterModel* model);

protected:
    BH1750 *device;
    FlashMeterModel *model;
    float previousLuxValue = -1.0;
    double speeds[28];

    int calculateSpeedIndex( int EV100, int sensibilityIndex, int focalIndex) const;
private:
    void buildSpArray();

};