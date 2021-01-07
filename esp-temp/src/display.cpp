#include <Arduino.h>
#include "lib/seg.h"
#include "display.h"
#include "timer.h"
#include "dht.h"

const uint8_t cathodes[] = {26,27,14,12}; // digits
const uint8_t anodes[] = {21, 19, 18, 5, 17, 16, 4, 2}; // segments

FourDigitSevenSegment segdisp (cathodes, anodes, COMMON_ANODE);

// refresh segdisp task
void refresh_display(void * parameter){
    uint8_t inc=0;
    DHT_DATA rx_data;
    while(1){
        xSemaphoreTake(tick, portMAX_DELAY);

        if (xQueueReceive(dht_queue, &rx_data, 0) == pdTRUE){
            Serial.print("display task recieved:");
            Serial.print(rx_data.type);
            Serial.print("|");
            Serial.println(rx_data.str);
        }
        switch (inc){
            case 0:
                show_digit(0, rx_data.str[0], false);
                inc++;
                break;
            case 1:
                if (rx_data.str[2] == '.'){
                    show_digit(1, rx_data.str[1], true);
                } else {
                    show_digit(1, rx_data.str[1], false);
                }
                inc++;
                break;
            case 2:
                show_digit(2, rx_data.str[3], false);
                inc++;
                break;
            case 3:
                show_digit(3, rx_data.str[4], false);
                inc=0;
                break;
        }
    }
    vTaskDelete(NULL);
}

// helper function to show digits
void show_digit(uint8_t digit, char c, bool period){
    segdisp.d(digit);
    segdisp.s(c);
    if (period){
        segdisp.s_dot_on();
    } else {
        segdisp.s_dot_off();
    }
}

