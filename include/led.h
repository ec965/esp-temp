#pragma once
#include <Arduino.h>

void blink_led(uint8_t, uint32_t);

void cycle_led(uint8_t, uint32_t);

void led_init();

void led_task(void*);

void only_green();
void only_red();
void only_blue();