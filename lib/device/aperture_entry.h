#pragma once

/**
 * Structure holding the different representations of an aperture.
 **/
class ApertureEntry
{
public:
    ApertureEntry();
    ApertureEntry(char *display, const double splimplified, const double value);
    ~ApertureEntry();
    double getSimplified() const { return mSimplified; }
    double getValue() const { return mValue; }
    char* getDisplay()const { return mDisplay;}

protected:
private:
    double mSimplified;
    double mValue;
    char* mDisplay;
};