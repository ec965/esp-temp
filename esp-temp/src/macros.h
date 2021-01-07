#pragma once

#define QSIZE 1
const uint8_t bx_pin = 33;
const uint8_t dht_pin = 25;

// 4 digit 7 segment display pins
const uint8_t cathodes[] = {26,27,14,12}; // digits
const uint8_t anodes[] = {21, 19, 18, 5, 17, 16, 4, 2}; // segments