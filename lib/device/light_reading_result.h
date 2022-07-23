#pragma once

class LightReadingResult
{

public:
    LightReadingResult(int mode, bool success, float lux, int EV_100);
    float getLux() const { return mLux; }
    int getEV100() const { return mEV_100; }
    bool isSuccess() const { return mSuccess; }

protected:
private:
    int mMode;
    bool mSuccess;
    float mLux;
    int mEV_100;
};