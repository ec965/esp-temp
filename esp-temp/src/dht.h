#pragma once
#include <Arduino.h>
#include "DHTesp.h"

#define TEMPC 0
#define HUM 1
#define TEMPF 2

#define DHTQSIZE 5

typedef struct dht_data{
    char str[DHTQSIZE];
    uint8_t type;
} DHT_DATA;

extern QueueHandle_t dht_queue;
extern DHTesp dht;
extern const int dht_pin;

void poll_sensor(void* paramater);
void dht_queue_init();
