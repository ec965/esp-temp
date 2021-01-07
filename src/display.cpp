#include <Arduino.h>
#include <Seg.h>
#include "display.h"
#include "timer.h"
#include "dht.h"
#include "config.h"


Display segdisp (digit_pins, seg_pins, COMMON_ANODE);

// refresh segdisp task
void refresh_display(void * parameter){
    DHT_DATA rx_data;

    while(1){
        xSemaphoreTake(tick_semaphore, portMAX_DELAY);

        if (xQueueReceive(dht_queue, &rx_data, 0) == pdTRUE){
            Serial.print("display task recieved:");
            Serial.print(rx_data.type);
            Serial.print("|");
            Serial.println(rx_data.str);
        }
        segdisp.display_string(rx_data.str);
    }
    vTaskDelete(NULL);
}


Display::Display(const uint8_t* d, const uint8_t* s, bool common)
    :FourDigitSevenSegment(d,s,common)
{
        digit_inc=0;
        dot_counter=0;
}

void Display::show_digit(uint8_t digit, char c, bool period){
    d(digit);
    s(c);
    if (period){
        s_dot_on();
    } else {
        s_dot_off();
    }
}

void Display::display_string(char* str){
    switch (digit_inc){
        case 0:
            if (str[1] == '.'){
                show_digit(0, str[0], true);
                dot_counter++;
            } else {
                show_digit(0, str[0], false);
            }
            digit_inc++;
            break;
        case 1:
            if (str[2+dot_counter] == '.'){
                show_digit(1, str[1+dot_counter], true);
            } else {
                show_digit(1, str[1+dot_counter], false);
            }
            digit_inc++;
            break;
        case 2:
            if (str[3+dot_counter] == '.'){
                show_digit(2, str[2+dot_counter], true);
            } else {
                show_digit(2, str[2+dot_counter], false);
            }
            digit_inc++;
            break;
        case 3:
            if (str[4+dot_counter] == '.'){
                show_digit(3, str[3+dot_counter], true);
            } else {
                show_digit(3, str[3+dot_counter], false);
            }
            digit_inc=0;
            dot_counter=0;
            break;
    }
}