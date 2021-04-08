#ifndef ARDUINO_CONSOLE_H
#define ARDUINO_CONSOLE_H

#include <console_delegator.h>
#include <Arduino.h>

class ArduinoConsole : public ConsoleDelegator
{

public:
    void print(char const *message)
    {
        Serial.print(message);
    };
    void println(char const *message)
    {
        Serial.println(message);
    };
};

#endif //ARDUINO_CONSOLE_H