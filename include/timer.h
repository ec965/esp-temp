#pragma once
#include <Arduino.h>
#define TIMERFREQ 1800

// create a binary semaphore for the tick that refreshes the display
extern SemaphoreHandle_t tick_semaphore;
// pointer to the timer
extern hw_timer_t* timer;

// timer interrupt callback to set refresh speed of 4digit7seg
void IRAM_ATTR onTimer();
// initialize the timer
void timer_init();
