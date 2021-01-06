#include <Arduino.h>
#include "seg.h"
const int cathodes[] = {26,27,14,12}; // digits
const int anodes[] = {21, 19, 18, 5, 17, 16, 4, 2}; // segments

FourDigitSevenSegment display(cathodes, anodes, COMMON_ANODE);

// create a binary semaphore for the tick that refreshes the display
SemaphoreHandle_t tick = xSemaphoreCreateBinary();
// timer stuff
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

// timer interrupt callback to set refresh speed of 4digit7seg
void IRAM_ATTR onTimer(){
    xSemaphoreGiveFromISR(tick, NULL);
}

// refresh display task
void refresh_display(void * parameter){
    int inc=0;
    while(1){
        xSemaphoreTake(tick, portMAX_DELAY);
        switch (inc){
            case 0:
                display.d(0);
                display.s(0);
                inc++;
                break;
            case 1:
                display.d(1);
                display.s(0);
                inc++;
                break;
            case 2:
                display.d(2);
                display.s(0);
                inc++;
                break;
            case 3:
                display.d(3);
                display.s_c();
                inc=0;
                break;
        }
    }
    vTaskDelete(NULL);
}


void setup() {
    Serial.begin(115200);
    Serial.println("Init display");
    if (!display.init()){
        Serial.println("Failed to initialize");
        while (1){}
    }

    // init display refresh interrupt timer
    timer = timerBegin(0,80,true); //set timer for microseconds
    timerAttachInterrupt(timer, &onTimer, true);
    timerAlarmWrite(timer, 17, true); // about 60hz
    timerAlarmEnable(timer);
    xTaskCreate(refresh_display, "refresh display", 1000, NULL, 1, NULL);
}

void loop() {
}
