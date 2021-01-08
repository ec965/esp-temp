#include <Arduino.h>
#include "led.h"

void blink_led(uint8_t pin, uint32_t duration){
    digitalWrite(pin, HIGH);
    vTaskDelay((duration/2));
    digitalWrite(pin, LOW);
    vTaskDelay((duration/2));
}