#ifndef GENERIC_LIGHT_SENSOR_H
#define GENERIC_LIGHT_SENSOR_H

class GenericLightSensorDevice{

    public:
        virtual float readLightLevel() = 0;
};

#endif //GENERIC_LIGHT_SENSOR_H