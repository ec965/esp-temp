#include <Arduino.h>
#include "timer.h"

// create a binary semaphore for the tick that refreshes the display
SemaphoreHandle_t tick = xSemaphoreCreateBinary();
// pointer to the timer
hw_timer_t* timer = NULL;

// timer interrupt callback to set refresh speed of 4digit7seg
void IRAM_ATTR onTimer(){
    xSemaphoreGiveFromISR(tick, NULL);
}

void timer_init(){
    // init display refresh interrupt timer
    timer = timerBegin(0,80,true); //set timer for microseconds
    timerAttachInterrupt(timer, &onTimer, true);
    timerAlarmWrite(timer, TIMERFREQ, true); // about 60hz
    timerAlarmEnable(timer);
}
