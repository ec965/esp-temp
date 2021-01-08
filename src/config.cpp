#include <Arduino.h>
#include "config.h"

const uint8_t onboardled_pin = 2;

const uint8_t bx_pin = 33;

const uint8_t dht_pin = 25;

// 4 digit 7 segment display pins
const uint8_t digit_pins[] = {26,27,14,12}; // digits
const uint8_t seg_pins[] = {21, 19, 18, 5, 17, 16, 4, 15}; // segments

// mqtt
const char* mqtt_client_id = "esp32-temp-0"; // name of this device
const char* mqtt_intopic = "esp32-temp/out"; // name of topic that this device is subbed to
const char* mqtt_outtopic = "esp32-temp/in"; // name of topic that this device publishes to

//------PRIVATE MACROS-----//
/*
const char* mqtt_server = "";
uint16_t mqtt_port = ;
const char* mqtt_username = "";
const char* mqtt_password = "";
*/