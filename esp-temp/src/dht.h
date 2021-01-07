#pragma once
#include <Arduino.h>
#include "DHTesp.h"

// types of data for dht data
#define TEMPC 0
#define HUM 1
#define TEMPF 2
// size of the string in dht_data struct 
#define DHTSIZE 5
#define QSIZE 5

// struct for dht queue data
typedef struct dht_data{
    char str[DHTSIZE];
    uint8_t type;
} DHT_DATA;

// queue for dht data
extern QueueHandle_t dht_queue;

extern DHTesp dht;
extern const int dht_pin;

// task to poll DHT11 sensor and send data to display
void poll_sensor(void* paramater);

void dht_queue_init();
