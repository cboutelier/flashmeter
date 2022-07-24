#pragma once

class ExposureProposal {

    public:

        ~ExposureProposal();
        double speed;
        double aperture;
        int iso;
        double ev;
        double lux;
        char* speedDisplay;
        void setSpeedDisplay( const char* s);

};