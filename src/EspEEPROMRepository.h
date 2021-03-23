#ifndef ESP_EPROM_REPOSITORY_H
#define ESP_EPROM_REPOSITORY_H

#include <repository.h>
#include <Arduino.h>


class EspEEPROMRepository : public Repository
{

public:
    EspEEPROMRepository(void (*attach)(), void (*detach)());
    virtual int loadKey(const char *key) const;
    virtual void saveKey(const char *key, int value);

protected:
    void (*attachInterruptCallback)();
    void (*detachInterruptCallback)();
};

#endif //ESP_EPROM_REPOSITORY_H