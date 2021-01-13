#pragma once
#include <Arduino.h>

extern SemaphoreHandle_t serial_semaphore;
// lock the serial port so serial writes don't overwrite each other
#define SERIALTAKE if (xSemaphoreTake(serial_semaphore, (TickType_t) 5) == pdTRUE){
#define SERIALGIVE xSemaphoreGive(serial_semaphore); }

extern const uint8_t onboardled_pin;

#define BXQSIZE 5
extern const uint8_t bx_pin;

// DHT11
#define SENSORQSIZE 5
#define STARTINGDT TEMPF // starting data type
extern const uint8_t dht_pin;
extern const float temp_calibration;
extern const float humi_calibration;
// types of data for dht data
#define TEMPC 0
#define HUMI 1
#define TEMPF 2

// 4 digit 7 segment display pins
extern const uint8_t digit_pins[]; // digits
extern const uint8_t seg_pins[]; // segments

// led pins
extern const uint8_t redled_pin;
extern const uint8_t blueled_pin;
extern const uint8_t greenled_pin;

// mqtt
#define MQTTPUBQSIZE 20
extern const char* mqtt_client_id; // name of this device
extern const char* mqtt_intopic; // name of topic that this device is subbed to
extern const char* mqtt_outtopic; // name of outtopic

//-----PRIVATE MACROS-----//
extern const char* mqtt_server;
extern uint16_t mqtt_port;
extern const char* mqtt_username;
extern const char* mqtt_password;