#include <Arduino.h>
#include "timer.h"

void Timer::init(uint8_t hw_timer, uint16_t divider, uint16_t tick_time){
    timer = timerBegin(hw_timer, divider, true); //count up
    timerAttachInterrupt(timer, (void(*)())&Timer::timer_callback, true);
    timerAlarmWrite(timer, tick_time, true);
    timerAlarmEnable(timer);
}

void Timer::wait_for_tick(){
    xSemaphoreTake(tick, portMAX_DELAY);
}

void IRAM_ATTR Timer::timer_callback(void){
    xSemaphoreGiveFromISR(tick, NULL);
}

SemaphoreHandle_t Timer::get_semaphore(){
    return tick;
}    

