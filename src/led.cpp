#include <Arduino.h>
#include "led.h"
#include <DHTesp.h>
#include "dht.h"
#include "config.h"

void blink_led(uint8_t pin, uint32_t duration){
    digitalWrite(pin, HIGH);
    vTaskDelay((duration/2));
    digitalWrite(pin, LOW);
    vTaskDelay((duration/2));
}

// requires ledc setup
void cycle_led(uint8_t pwm_channel, uint32_t duration){
    uint8_t i;
    for(i=0; i<255; i++){
        ledcWrite(pwm_channel, i);
        vTaskDelay( (duration/2) / 255 );
    }
    for(i=0; i<255; i++){
        ledcWrite(pwm_channel, i);
        vTaskDelay( (duration/2) / 255 );
    }
}

void led_init(){
    pinMode(greenled_pin, OUTPUT);
    pinMode(redled_pin, OUTPUT);
    pinMode(blueled_pin, OUTPUT);
    pinMode(onboardled_pin, OUTPUT);
}

void led_task(void* parameter){
    ComfortState comfort;
    DHT_DATA display_data;
    while(1){
        // in the sensor task, dht_queue is activated first
        xQueuePeek(dht_queue, &display_data, portMAX_DELAY);
        xQueueReceive(comfort_queue, &comfort, portMAX_DELAY);
        switch(comfort) {
            case Comfort_OK:
                only_green();
                break;
            case Comfort_TooHot:
                if (display_data.type == HUMI){
                    only_red();
                } else { // data type is TEMP related
                    only_green();
                }
                break;
            case Comfort_TooCold:
                if (display_data.type == HUMI){
                    only_green();
                } else { // data type is TEMP related
                    only_blue();
                }
                break;
            case Comfort_TooDry:
                if (display_data.type == HUMI){
                    only_blue();
                } else { // data type is TEMP related
                    only_green();
                }
                break;
            case Comfort_TooHumid:
                if (display_data.type == HUMI){
                    only_red();
                } else { // data type is TEMP related
                    only_green();
                }
                break;
            case Comfort_HotAndHumid:
                only_red();
                break;
            case Comfort_HotAndDry:
                if (display_data.type == HUMI){
                    only_blue();
                } else { // data type is TEMP related
                    only_red();
                }
                break;
            case Comfort_ColdAndHumid:
                if (display_data.type == HUMI){
                    only_red();
                } else { // data type is TEMP related
                    only_blue();
                }
                break;
            case Comfort_ColdAndDry:
                only_blue();
                break;
            default:
                break;
        }
    }
    vTaskDelete(NULL);
}

void only_green(){
    digitalWrite(greenled_pin, HIGH);
    digitalWrite(blueled_pin, LOW);
    digitalWrite(redled_pin, LOW);
}
void only_red(){
    digitalWrite(greenled_pin, LOW);
    digitalWrite(blueled_pin, LOW);
    digitalWrite(redled_pin, HIGH);
}
void only_blue(){
    digitalWrite(greenled_pin, LOW);
    digitalWrite(blueled_pin, HIGH);
    digitalWrite(redled_pin, LOW);;
}