#include "arduino_timer_service.h"

 ArduinoTimerService::ArduinoTimerService(ConsoleDelegator *console, void (*onStartCallback)(), void (*onEndCallback)(), void (*onTickCallback)())
{
    this->console = console;
    this->tick = onTickCallback;
    this->onTimerStart = onStartCallback;
    this->onTimerStop = onEndCallback;
    timer = timerBegin(0, 80, true);

    if (tick != nullptr && timer != nullptr)
    {
        timerAlarmWrite(timer, 1000000, true);
        timerAttachInterrupt(timer, this->tick, true);
    }
}
 
/*
ArduinoTimerService::ArduinoTimerService(ConsoleDelegator *console)
{
    this->console = console;
    timer = timerBegin(0, 80, true);

    if (tick != nullptr && timer != nullptr)
    {
        timerAlarmWrite(timer, 1000000, true);
        timerAttachInterrupt(timer, this->tick, true);
    }
}*/

void ArduinoTimerService::enableAlarm()
{
    this->console->println("Enable alarm");

 if (tick != nullptr && timer != nullptr)
    {
      
        timerAlarmEnable(timer);
    }
    
}

void ArduinoTimerService::disableAlarm()
{
    this->console->println("disable alarm");

    if (timer != nullptr)
    {
        timerAlarmDisable(timer);
    }
}

 