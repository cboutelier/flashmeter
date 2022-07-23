#include "exposure_calculator.h"
#include "shutter_speed_full_stop.h"

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

ExposureCalculator::ExposureCalculator()
{
    initApertures(20);
    initShutterSpeeds(19);
}

ExposureCalculator::~ExposureCalculator()
{
    for (int i = 0; i < 20; i++)
    {
        delete this->apertures[i];
    }
    delete this->apertures;

    for (int i = 0; i < 19; i++)
    {
        delete this->shutterSpeeds[i];
    }
    delete this->shutterSpeeds;
}


void ExposureCalculator::initApertures(const int number)
{
    this->apertures = new ApertureEntry *[number];

    for (int i = 0; i < number; i++)
    {
        if (i == 0)
        {
            char display[3];
            sprintf(display, "f/1");
            this->apertures[i] = new ApertureEntry(display, 1, 1);
        }
        else
        {
            char display[10];
            double newAperture = 1 * pow(sqrt(2), i);
            double newApertureSimplified = 0;
            // Above ten, the aperture is truncated.
            if (newAperture >= 10)
            {
                newApertureSimplified = floor(newAperture);
                sprintf(display, "f/%.0f", newApertureSimplified);
            }
            else
            {
                if (abs((trunc(newAperture * 100) / 100) - newAperture) > 0.001)
                {
                    newApertureSimplified = trunc(newAperture * 10) / 10;
                    sprintf(display, "f/%.1f", newApertureSimplified);
                }
                else
                {
                    newApertureSimplified = newAperture;
                    sprintf(display, "f/%.f", newApertureSimplified);
                }
            }

            this->apertures[i] = new ApertureEntry(display, newApertureSimplified, newAperture);
        }
    }
}



ApertureEntry **ExposureCalculator::getApertures()
{
    return this->apertures;
}

ShutterSpeedEntry **ExposureCalculator::getShutterSpeeds()
{
    return this->shutterSpeeds;
}

ExposureProposal* ExposureCalculator::getSettingsForDefinedAperture(const LightReadingResult *reading, const double aperture, const int iso) const
{
    if (reading == nullptr || !reading->isSuccess() || iso <= 0)
    {
        return nullptr;
    }
    else
    {
        //Rule EV10 f/5.6 s=1/30
        int EVoffset= 10-reading->getEV100();
        int isoOffset = this->getEVOffset(iso);
        int apertureOffset = this->getApertureOffset( 5.6, aperture );
        cout << "Aperture offset ("<<5.6 <<"|"<<aperture<< "): " << apertureOffset << endl;
        int globalOffset = EVoffset+isoOffset + apertureOffset;

        //for aperture : 5.6, time would be 1/30-(isoOffset+EVoffset)stops
        ExposureProposal* result = new ExposureProposal();
        result->iso = iso;
        result->aperture = aperture;
        result->ev = reading->getEV100();
        result->lux = reading->getLux();
        //find the speed for 5.6 / @100
        int index = 0;
        for( int j = 0; j < 12; j++){
            ShutterSpeedEntry* entry = shutterSpeeds[j];
           // cout << "Test: " << entry->getDisplay() << " " << entry->getValue() << " " << abs(entry->getValue()-(1/30.0)) << endl;
            if( abs(entry->getValue()-(1/30.0)) < 0.01){
                index = j;
                break;
            }
        }
        cout << "Index is " << index << endl;
        cout << "Global offset " << globalOffset << endl; 
        index += globalOffset;
        result->speed = this->shutterSpeeds[index]->getValue();
        result->setSpeedDisplay(this->shutterSpeeds[index]->getDisplay());

        return result; 
    }
}
void ExposureCalculator::getSettingsForDefinedSpeed(const LightReadingResult *reading, const int iso) const
{
    if (reading == nullptr || !reading->isSuccess() || iso <= 0)
    {
        return;
    }
    else
    {
    }
}

int ExposureCalculator::getApertureOffset( const double baseAperture, const double desiredAperture) const{
    cout << "--------------------------------------------------------------" <<endl;
    if( baseAperture==desiredAperture){
        return 0;
    }
    int baseIndex= -1;
    int desiredIndex = -1;
    for( int j = 0; j < 20;  j++){
        ApertureEntry* entry = this->apertures[j];
        cout << "Value: " << entry->getValue() << " base aperture:" << baseAperture << " abs: "<<  abs(entry->getValue()-baseAperture)  << endl;
        if( (abs(entry->getValue()-baseAperture)) < 0.35){
            baseIndex = j;
            cout << "Found base Index: " << entry->getDisplay() <<endl;
        }
         if( (abs(entry->getValue()-desiredAperture)) < 0.35){
            desiredIndex = j;
            cout << "Found desired Index: " << entry->getDisplay() <<endl;
        }

    }
    return desiredIndex-baseIndex;
}
/**
 * Returns the number of stops (positive/negative) to apply with provided parameter vs 100 iso.
 * Exemples:
 * - ISO 200 = minus one stop
 * - ISO 400 = minus two stops
 * - ISO 50 = one stop
 * - ISO 25 = two stops
 **/
double ExposureCalculator::getEVOffset(const int iso) const
{

    if (iso == 0)
    {
        throw InvalidIsoException("ISO 0 is invalid");
    }
    double ratio = iso / 100.0;
    return -1.0 * (log(ratio) / log(2));
}

/**
 * Returns the standardized aperture given the submitted aperture.
 * if strict is false, the closest is returned
 * if strict is true, return the value if exist, exception otherwise
 * */
double ExposureCalculator::getAperture(const double submittedAperture, bool strict) const
{
    double lowerBound = 0;
    double upperBound = 10000;
    int count = 20;
    bool lowerFound = false;
    bool upperFound = false;
    for (int j = 0; j < count; j++)
    {

        ApertureEntry *aperture = this->apertures[j];

        if (aperture->getValue() <= submittedAperture)
        {
            lowerBound = aperture->getSimplified();
        }
        else
        {
            lowerFound = true;
        }
        if (aperture->getValue() >= submittedAperture && lowerFound && !upperFound)
        {
            upperBound = aperture->getSimplified();
            upperFound = true;
        }
        if (upperFound && lowerFound)
        {
            break;
        }
    }
    double distanceToLowerBound = submittedAperture - lowerBound;
    double distanceToUpperBound = upperBound - submittedAperture;
    if (distanceToLowerBound < distanceToUpperBound)
    {
        return lowerBound;
    }
    return upperBound;
}

void ExposureCalculator::initShutterSpeeds(const int number)
{
    this->shutterSpeeds = new ShutterSpeedEntry *[number];
    for( int i = 0; i < 12; i++){
        const char* display = speed_full[i*2];
        const char* speedAsChar = speed_full[(i*2)+1];
        double speed = std::stod(speedAsChar);
        ShutterSpeedEntry* entry = new ShutterSpeedEntry(display, speed);
        this->shutterSpeeds[i] = entry;
    }
}