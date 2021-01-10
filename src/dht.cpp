#include <Arduino.h>
#include <DHTesp.h>
#include "dht.h"
#include "config.h"
#include "bx.h"
#include "connect.h"

// Queue from dht task to display task
QueueHandle_t dht_queue;
QueueHandle_t comfort_queue; // comfort ratio
DHTesp dht;


void sensor_task(void* parameter){
    uint8_t data_type = STARTINGDT;
    TempAndHumidity data;
    ComfortState comfort;
    
    vTaskDelay(1000 / portTICK_PERIOD_MS); //give the sensor some time to start up

    while(1){
        // poll DHT11 and update temperature
        data = dht.getTempAndHumidity();
        if (dht.getStatus() != 0){
            Serial.println("SENSOR TASK: failed to get data");
        } else {
            data.temperature += temp_calibration;
            data.humidity += humi_calibration;
            // get the comfort level
            dht.getComfortRatio(comfort, data.temperature, data.humidity);

            Serial.print("SENSOR TASK\n\tTemp:");
            Serial.println(data.temperature);
            Serial.print("\tHumi: ");
            Serial.println(data.humidity);
            Serial.print("\tComfort Status:");
            Serial.println(comfort);

            // publish sensor reading to MQTT
            MQTT_PUB_ITEM mqtt_item;
            sprintf(mqtt_item.topic,"%s/dht11", mqtt_outtopic);
            sprintf(mqtt_item.payload, "$temp:%f;humi:%f#", data.temperature, data.humidity);
            Serial.println("SENSOR TASK -> mqtt_pub_queue -> MQTT TASK:");
            Serial.print("\tTOPIC:");
            Serial.println(mqtt_item.topic);
            Serial.print("\tPAYLOAD");
            Serial.println(mqtt_item.payload);
            if (xQueueSend(mqtt_pub_queue, &mqtt_item, 5000 / portTICK_PERIOD_MS) == pdFALSE){
                Serial.println("SENSOR TASK: mqtt_pub_queue: failed to send");
            }
            
            // send dht data to display
            enqueue_dht_data(data, data_type);

            // enqueue comfort
            Serial.print("SENSOR TASK -> comfort_queue -> LED TASK:");
            Serial.println(comfort);
            if (xQueueSend(comfort_queue, &comfort, 5000 / portTICK_PERIOD_MS) == pdFALSE){
                Serial.println("SENSOR TASK: comfort_queue: failed to send");
            }

        } 
        
        // uses queue timer as a delay
        if (xQueueReceive(bx_queue, &data_type, 5000 / portTICK_PERIOD_MS) == pdTRUE){
            enqueue_dht_data(data, data_type);
        }
    }
    vTaskDelete(NULL);
}

void enqueue_dht_data(TempAndHumidity data, uint8_t data_type){
    DHT_DATA tx_data; //struct to hold tx data
    
    switch (data_type){
        case(TEMPC):
            sprintf(tx_data.str, "%.*fc", 1, data.temperature);
            tx_data.type=TEMPC;
            break;            
        case(HUMI):
            sprintf(tx_data.str, "%.*fh", 1, data.humidity);
            tx_data.type=HUMI;
            break;            
        case(TEMPF):
            float tempf = (data.temperature * 1.8) + 32;
            sprintf(tx_data.str, "%.*ff", 1, tempf);
            tx_data.type=TEMPF;
            break;
    }
    Serial.print("SENSOR TASK -> dht_queue -> DISPLAY TASK:");
    Serial.print(tx_data.type);
    Serial.print("|");
    Serial.println(tx_data.str);

    if (xQueueSend(dht_queue, &tx_data, 5000 / portTICK_PERIOD_MS) == pdFALSE){
        Serial.println("SENSOR TASK: dht_queue: failed to send");
    }
}

void dht_init(){
    dht.setup(dht_pin, DHTesp::DHT11);

    dht_queue = xQueueCreate(SENSORQSIZE, sizeof(DHT_DATA));
    if (dht_queue == NULL){
        Serial.println("dht_queue: error creating queue");
    }

    comfort_queue = xQueueCreate(SENSORQSIZE, sizeof(ComfortState));
    if (comfort_queue == NULL){
        Serial.println("comfort_queue: error creating queue");
    }
}