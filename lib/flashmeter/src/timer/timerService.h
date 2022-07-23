#ifndef TIMER_SERVICE_H
#define TIMER_SERVICE_H
#include "../console_delegator.h"

/**
 * @brief What is a timer service? A timer service is a service that can handle time event: based on a total duration and an interval, the timer may fire 3 types of event, the start event, the end event and the tick event.
 * Tick event is fired after each interval period until the end.
 *
 */
class TimerService
{

public:
    virtual void enableAlarm() = 0;
    virtual void disableAlarm() = 0;

protected:
    void (*tick)();
    void (*onTimerStart)();
    void (*onTimerStop)();
    ConsoleDelegator *console;
     void *model;
};
#endif // TIMER_SERVICE_H