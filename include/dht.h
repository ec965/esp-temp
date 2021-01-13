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
// queue for comfort ratio: data goes to led task
extern QueueHandle_t comfort_queue; // comfort ratio

extern DHTesp dht;

// task to poll DHT11 sensor and send data to display
void sensor_task(void* paramater);

void enqueue_dht_for_display(TempAndHumidity data, uint8_t data_type);

void enqueue_dht_for_mqtt(float data, const char* unit, const char* topic);

void dht_init();
