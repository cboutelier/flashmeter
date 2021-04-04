#ifndef INFO_AREA_H
#define INFO_AREA_H


#include "area.h"
#include "../../console_delegator.h"

class InfoArea : public Area
{

private:
    void displaySensitivity(const int yBaseLine, const int fontSize);
    void displayLuxValue( const int yBaseLine, const int fontSize);
    void displayEVValue( const int yBaseLine, const int fontSize);
    ConsoleDelegator* console;

protected:
    int sensitivity = 0;
    char sensitivityValue[20];
    double luxValue = 0.0;
    int evValue = 0;
    bool sensitivityChanged = true;
    bool luxValueChanged = true;
    bool evValueChanged = true;

public:
    InfoArea(DisplayDevice *d, ConsoleDelegator *console,  int x, int y, int width, int height);
    virtual void show();
    virtual void fillArea();
    virtual void onReceiveDataFromSubject(const Observable *model);
    void setSensitivity(const int s) { this->sensitivity = s; }
    int getSensitivity() const { return this->sensitivity; }
    void setLuxValue( const double lux) { this->luxValue = lux; }
    double getLuxValue() const { return this->luxValue; }
    void setSensitivityValue(const char *value);
    const char* getSensitvityValue() const;
};

#endif //INFO_AREA_H