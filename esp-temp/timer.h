#pragma once

class Timer{
    private:
        SemaphoreHandle_t tick = xSemaphoreCreateBinary();
        hw_timer_t* timer = NULL;
    public: 
       // divider = what to divide the base clock freq by
       //   base clock for my board is 80Mhz
       // hw_timer can be values from: 0 to 3
       //   there are four hardware timers
       // tick_time is the time for 1 tick based on the value of (base clock/divider)
        void init(uint8_t hw_timer, uint16_t divider, uint16_t tick_time);

        void wait_for_tick();
        void IRAM_ATTR timer_callback(void);
        SemaphoreHandle_t get_semaphore();
};
