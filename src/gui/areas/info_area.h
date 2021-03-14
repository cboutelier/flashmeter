#ifndef INFO_AREA_H
#define INFO_AREA_H

#include <Arduino.h>

#include "area.h"

class InfoArea : public Area
{

private:
    void displaySensitivity(const int yBaseLine, const int fontSize);
    void displayLuxValue( const int yBaseLine, const int fontSize);

protected:
    int sensitivity = 0;
    double luxValue = 0.0;

public:
    using Area::Area;
    virtual void show();
    void onReceiveDataFromSubject(const FlashMeterModel *model);
    void setSensitivity(const int s) { this->sensitivity = s; }
    int getSensitivity() const { return this->sensitivity; }
    void setLuxValue( const double lux) { this->luxValue = lux; }
    double getLuxValue() const { return this->luxValue; }
};

#endif //INFO_AREA_H