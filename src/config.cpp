#include <Arduino.h>
#include "config.h"

const uint8_t bx_pin = 33;

const uint8_t dht_pin = 25;

// 4 digit 7 segment display pins
const uint8_t digit_pins[] = {26,27,14,12}; // digits
const uint8_t seg_pins[] = {21, 19, 18, 5, 17, 16, 4, 2}; // segments

// mqtt
const char* mqtt_client_id = "esp32-temp"; // name of this device
const char* mqtt_intopic = "esp32-temp/out"; // name of topic that this device is subbed to

//------PRIVATE MACROS-----//
/*
const char* ssid = "";
const char* password = "";
const char* mqtt_server = "";
uint16_t mqtt_port = ;
*/