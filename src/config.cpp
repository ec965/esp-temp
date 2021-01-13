#include <Arduino.h>
#include "config.h"

SemaphoreHandle_t serial_semaphore;

const uint8_t onboardled_pin = 2;

const uint8_t bx_pin = 33;

const uint8_t dht_pin = 13;
const float temp_calibration= 0;
const float  humi_calibration = 0;

// 4 digit 7 segment display pins
const uint8_t digit_pins[] = {14, 4, 16, 5}; // digits
const uint8_t seg_pins[] = {12, 17, 19, 22, 23, 15, 18, 21}; // segments

// led pins
const uint8_t redled_pin = 32;
const uint8_t blueled_pin = 25;
const uint8_t greenled_pin = 26;

// mqtt
const char* mqtt_client_id = "esp32-temp-0"; // name of this device
const char* mqtt_intopic = "esp32-temp/out/#"; // name of topic that this device is subbed to
const char* mqtt_outtopic = "esp32-temp/in"; // name of topic that this device publishes to

//------PRIVATE MACROS-----//
/*
const char* mqtt_server = "";
uint16_t mqtt_port = ;
const char* mqtt_username = "";
const char* mqtt_password = "";
*/

// 0 - boot
// 1 - tx
// 2 - onboard led
// 3 - rx
// 4 - seg
// 5 - seg
// 12 - dig
// 13 - null 
// 14 - dig
// 15 - seg
// 16 - seg
// 17 - seg
// 18 - seg
// 19 - seg
// 21 - seg
// 22 - null=
// 23 - null
// 25 - dht
// 26 - dig
// 27 - dig
// 32 - null
// 33 - button

// 19 GPIO
// -12 display
// -1 button 
// -1 dht11
// -1 builtin-led
// ----
// 4 leftover
