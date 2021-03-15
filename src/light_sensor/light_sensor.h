#pragma once

#include <Arduino.h>
#include <BH1750.h>
#include "../flashmeter_model.h"

class LightSensor{

    public :
        LightSensor( BH1750* device, FlashMeterModel* model );
        void read();


    protected:
            BH1750* device;
            FlashMeterModel* model; 
            float previousLuxValue = -1.0;
};