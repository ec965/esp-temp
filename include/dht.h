#pragma once
#include <Arduino.h>
#include "DHTesp.h"

// size of the string in dht_data struct 
#define DHTSIZE 6 // strings are normally: "16.5C\0" which is 6 chars

// struct for dht queue data
typedef struct dht_data{
    char str[DHTSIZE];
    uint8_t type;
} DHT_DATA;

// queue for dht data
extern QueueHandle_t dht_queue;

extern DHTesp dht;

// task to poll DHT11 sensor and send data to display
void sensor_task(void* paramater);

void enqueue_dht_data(TempAndHumidity data, uint8_t data_type);

void dht_init();
