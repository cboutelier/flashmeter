#ifndef ESP_EPROM_REPOSITORY_H
#define ESP_EPROM_REPOSITORY_H

#include <repository.h>
#include <Arduino.h>

class EspEEPROMRepository : public Repository
{

public:
    EspEEPROMRepository(void (*attach)(), void (*detach)());
    virtual int loadKey(char const *key);
    virtual void saveKey(char const *key, int value);

protected:
    void (*attachInterruptCallback)();
    void (*detachInterruptCallback)();
    int getAddress(char const *key);
};

#endif //ESP_EPROM_REPOSITORY_H