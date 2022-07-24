#pragma once
#include "light_reading_result.h"
#include "aperture_entry.h"
#include "shutter_speed_entry.h"
#include "exposure_proposal.h"
#include <math.h>

#define ISO_EXCEPTION_VALUE -9999

class ExposureCalculator
{
public:
    ExposureCalculator();
    ~ExposureCalculator();
    double getAperture(const double submittedAperture, bool strict) const;
    // void getSettingForDefinedApertureAt100ISO( const LightReadingResult* reading, float aperture) const;
    void getSettingsForDefinedSpeed(const LightReadingResult *reading, const int iso) const;
    ExposureProposal* getSettingsForDefinedAperture(const LightReadingResult *reading, const double aperture, const int iso) const;

    /**
     * Returns the number of stops (positive/negative) to apply with provided parameter vs 100 iso.
     **/
    double getEVOffset(const int iso) const;
    int getApertureOffset( const double baseAperture, const double desiredAperture) const;
    ApertureEntry** getApertures();
    ShutterSpeedEntry** getShutterSpeeds();

protected:
private:
    ApertureEntry **apertures;
    ShutterSpeedEntry **shutterSpeeds;
    void initApertures(const int size);
    void initShutterSpeeds(const int size);
    int speedCounts = 12;
};