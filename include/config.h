#pragma once
#include <Arduino.h>

#define BXQSIZE 1
extern const uint8_t bx_pin;

#define SENSORQSIZE 1
extern const uint8_t dht_pin;

// 4 digit 7 segment display pins
extern const uint8_t digit_pins[]; // digits
extern const uint8_t seg_pins[]; // segments

// mqtt
#define MQTTPUBQSIZE 10
extern const char* mqtt_client_id; // name of this device
extern const char* mqtt_intopic; // name of topic that this device is subbed to

//-----PRIVATE MACROS-----//
extern const char* ssid;
extern const char* password;
extern const char* mqtt_server;
extern uint16_t mqtt_port;
extern const char* mqtt_username;
extern const char* mqtt_password;