#pragma once
#include <Arduino.h>
#include "DHTesp.h"

// types of data for dht data
#define TEMPC 0
#define HUMI 1
#define TEMPF 2
// size of the string in dht_data struct 
#define DHTSIZE 5

// struct for dht queue data
typedef struct dht_data{
    char str[DHTSIZE];
    uint8_t type;
} DHT_DATA;

// queue for dht data
extern QueueHandle_t dht_queue;

extern DHTesp dht;

// task to poll DHT11 sensor and send data to display
void poll_sensor(void* paramater);

void enqueue_dht_data(TempAndHumidity data, uint8_t data_type);

void dht_init();

uint8_t change_data_type(uint8_t data_type);