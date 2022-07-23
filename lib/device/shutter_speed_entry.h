#pragma once

/**
 * Structure holding the different representations of shutter speed.
 **/
class ShutterSpeedEntry
{
public:
    ShutterSpeedEntry();
    ShutterSpeedEntry(const char *display,  const double value);
    ~ShutterSpeedEntry();
    
    double getValue() const { return mValue; }
    char* getDisplay()const { return mDisplay;}

protected:
private:
   
    double mValue;
    char* mDisplay;
    bool mFull;
    bool mHalf;
    bool mThird;
};