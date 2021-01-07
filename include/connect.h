#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#define TOPICSIZE 56
#define PAYLOADSIZE 200
extern PubSubClient mqtt_client;
extern QueueHandle_t mqtt_pub_queue;

typedef struct MQTT_PUB_ITEM{
    char topic[TOPICSIZE];
    char payload[PAYLOADSIZE];
} MQTT_PUB_ITEM;

// setup wifi
void network_init();
// init mqtt pub queue
void mqtt_pubq_init();
// mqtt callback, this function is run whenever a message is recieved
void mqtt_callback(char*, uint8_t*, unsigned int);
// mqtt_reconnect will be attempted whenever the connection w/ server is lost
void mqtt_reconnect();
// mqtt publishing task
void mqtt_publisher(void* parameter);

