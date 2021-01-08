#include <Arduino.h>
#include "led.h"

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