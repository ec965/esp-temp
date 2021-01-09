#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "config.h"
#include "connect.h"
#include "led.h"
#include "bx.h"

WiFiClient esp_client;
PubSubClient mqtt_client(esp_client);

QueueHandle_t mqtt_pub_queue;

// setup mqtt
void mqtt_init(){
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
    uint8_t sensor_data_type, i;
    String string_msg;
    Serial.print("MQTT RX\n\tTOPIC:");
    Serial.println(topic);
    Serial.print("\tPAYLOAD:");
    for(i=0; i<length; i++){
        Serial.print((char)message[i]);
        string_msg += (char)message[i];
    }
    Serial.println();

    if (string_msg == "TEMPC"){
        sensor_data_type = TEMPC;
    } else if (string_msg == "HUMI") {
        sensor_data_type = HUMI;
    } else if (string_msg == "TEMPF") {
        sensor_data_type = TEMPF;
    } else {
        return;
    }
    Serial.print("MQTT TASK -> SENSOR TASK:");
    Serial.println(string_msg);
    xQueueSend(bx_queue, &sensor_data_type, 0); // don't block
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

            blink_led(onboardled_pin, 1000 / portTICK_PERIOD_MS);
            vTaskDelay(4000 / portTICK_PERIOD_MS);
        }
    }
}

void mqtt_pub_task(void* parameter){
    MQTT_PUB_ITEM item;
    while(1){
        if (!mqtt_client.connected()){
            mqtt_reconnect();
        }
        if (xQueueReceive(mqtt_pub_queue, &item, 10 / portTICK_PERIOD_MS) == pdTRUE){
            Serial.print("MQTT TX\n\tTOPIC:");
            Serial.println(item.topic);
            Serial.print("\tPAYLOAD:");
            Serial.println(item.payload);
            mqtt_client.publish(item.topic, item.payload);
        }
        mqtt_client.loop(); // callback loop
    }
    vTaskDelete(NULL);
}

