#include <Arduino.h>
#include "seg.h"
#include "timer.h"
const uint8_t cathodes[] = {26,27,14,12}; // digits
const uint8_t anodes[] = {21, 19, 18, 5, 17, 16, 4, 2}; // segments

FourDigitSevenSegment display(cathodes, anodes, COMMON_ANODE);

SemaphoreHandle_t tick = xSemaphoreCreateBinary();
Timer seg_timer(&tick);

// refresh display task
void refresh_display(void * parameter){
    uint8_t inc=0;
    while(1){
        xSemaphoreTake(tick, portMAX_DELAY);
        Serial.println("got tick");
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
    seg_timer.init(0, 80, 1600);
    xTaskCreate(refresh_display, "refresh display", 1000, NULL, 1, NULL);
}

void loop() {
}
