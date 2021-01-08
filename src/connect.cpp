#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "config.h"
#include "connect.h"

WiFiClient esp_client;
PubSubClient mqtt_client(esp_client);

QueueHandle_t mqtt_pub_queue;

// setup wifi and mqtt
void network_init(){
    WiFi.begin(ssid, password);

    Serial.print("connecting to wifi");
    while (WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.print('.');
    }
    Serial.println("\nconnected to wifi");

    mqtt_client.setServer(mqtt_server, mqtt_port);
    mqtt_client.setCallback(mqtt_callback);
    Serial.println("mqtt initialized");
    mqtt_pubq_init();
}

void mqtt_pubq_init(){
    mqtt_pub_queue = xQueueCreate(MQTTPUBQSIZE, MQTT_MAX_PACKET_SIZE);
    // default MQTT_MAX_PACKET_SIZE is 256 bytes
    if (mqtt_pub_queue == NULL){
        Serial.println("Error creating the mqtt pub queue");
    }
}

// mqtt callback, this function is run whenever a message is recieved
void mqtt_callback(char* topic, uint8_t* message, unsigned int length){
    int i;
    Serial.print("MQTT RX TOPIC:");
    Serial.print(topic);
    Serial.print("||PAYLOAD:");
    for(i=0; i<length; i++){
        Serial.print((char)message[i]);
    }
}

// mqtt_reconnect will be attempted whenever the connection w/ server is lost
void mqtt_reconnect() {
    while(!mqtt_client.connected()){
        Serial.print("attempting mqtt connection: ");

        if (mqtt_client.connect(mqtt_client_id, mqtt_username, mqtt_password)){
            Serial.println("connected");
            mqtt_client.subscribe(mqtt_intopic);
        } else {
            Serial.print("failed, rc=");
            Serial.print(mqtt_client.state());
            Serial.println("trying again in 5 sec.");
            vTaskDelay( 5000 / portTICK_PERIOD_MS); // don't block other tasks 
        }
    }
}

void mqtt_publisher(void* parameter){
    MQTT_PUB_ITEM item;
    while(1){
        if (!mqtt_client.connected()){
            mqtt_reconnect();
        }
        if (xQueueReceive(mqtt_pub_queue, &item, 10 / portTICK_PERIOD_MS) == pdTRUE){
            Serial.print("MQTT TX TOPIC:");
            Serial.print(item.topic);
            Serial.print("||PAYLOAD:");
            Serial.println(item.payload);
            mqtt_client.publish(item.topic, item.payload);
        }
        mqtt_client.loop();
    }
    vTaskDelete(NULL);
}

