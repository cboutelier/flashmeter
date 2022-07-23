#ifndef ARDUINO_TIMER_SERVICE_H
#define ARDUINO_TIMER_SERVICE_H

#include <Arduino.h>
#include <timer/timerService.h>
#include <console_delegator.h>

class ArduinoTimerService : public TimerService
{

public:
   ArduinoTimerService(ConsoleDelegator *console, void (*onStartCallback)(), void (*onEndCallback)(), void (*onTickCallback)());

  // ArduinoTimerService(ConsoleDelegator *console);
   void enableAlarm();
   void disableAlarm();

private:
   hw_timer_t *timer = nullptr;
  
};

#endif // ARDUINO_TIMER_SERVICE_H