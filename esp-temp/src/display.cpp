#include <Arduino.h>
#include <Seg.h>
#include "display.h"
#include "timer.h"
#include "dht.h"
#include "macros.h"


FourDigitSevenSegment segdisp (cathodes, anodes, COMMON_ANODE);

uint8_t digit_inc; // incrementer for switching digits

// refresh segdisp task
void refresh_display(void * parameter){
    DHT_DATA rx_data;
    digit_inc=0;
    while(1){
        xSemaphoreTake(tick_semaphore, portMAX_DELAY);

        if (xQueueReceive(dht_queue, &rx_data, 0) == pdTRUE){
            Serial.print("display task recieved:");
            Serial.print(rx_data.type);
            Serial.print("|");
            Serial.println(rx_data.str);
        }
        show_dht_data(rx_data.str);
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

void show_dht_data(char* str){
    switch (digit_inc){
        case 0:
            show_digit(0, str[0], false);
            digit_inc++;
            break;
        case 1:
            if (str[2] == '.'){
                show_digit(1, str[1], true);
            } else {
                show_digit(1, str[1], false);
            }
            digit_inc++;
            break;
        case 2:
            show_digit(2, str[3], false);
            digit_inc++;
            break;
        case 3:
            show_digit(3, str[4], false);
            digit_inc=0;
            break;
    }
}