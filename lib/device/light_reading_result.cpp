#include "light_reading_result.h"

LightReadingResult::LightReadingResult(int mode, bool success, float lux, int EV_100)
{
    this->mMode = mode;
    this->mSuccess = success;
    this->mLux = lux;
    this->mEV_100 = EV_100;

}