#include <Arduino.h>
#include "DHTesp.h"
#include "dht.h"
#include "config.h"
#include "bx.h"
#include "connect.h"

// Queue from dht task to display task
QueueHandle_t dht_queue;
DHTesp dht;


void sensor_task(void* parameter){
    uint8_t data_type = TEMPC;
    TempAndHumidity prev_data;
    ComfortState cf;
    prev_data.temperature = 0;
    prev_data.humidity = 0;
    
    vTaskDelay(1000 / portTICK_PERIOD_MS); //give the sensor some time to start up

    while(1){
        // poll DHT11 and update temperature
        TempAndHumidity data = dht.getTempAndHumidity();
        if (dht.getStatus() != 0){
            Serial.println("SENSOR TASK: failed to get data");
        } else {
            // get the comfort level
            float cr = dht.getComfortRatio(cf, data.temperature, data.humidity);

            Serial.print("SENSOR TASK\n\tTemp:");
            Serial.println(data.temperature);
            Serial.print("\tHumi: ");
            Serial.println(data.humidity);
            Serial.print("\tComfort Status:");
            Serial.println(cf);

            // publish sensor reading to MQTT
            MQTT_PUB_ITEM mqtt_item;
            sprintf(mqtt_item.topic,"%s/dht11", mqtt_outtopic);
            sprintf(mqtt_item.payload, "$temp:%f;humi:%f#", data.temperature, data.humidity);
            xQueueSend(mqtt_pub_queue, &mqtt_item, portMAX_DELAY);
            
            // send dht data to display
            enqueue_dht_data(data, data_type);
            // save the data in case we change display data before another sensor read is called
            prev_data = data;
        } 
        
        // uses queue timer as a delay
        if (xQueueReceive(bx_queue, &data_type, 10000 / portTICK_PERIOD_MS) == pdTRUE){
            enqueue_dht_data(prev_data, data_type);
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
    Serial.print("SENSOR TASK -> DISPLAY TASK:");
    Serial.print(tx_data.type);
    Serial.print("|");
    Serial.println(tx_data.str);

    xQueueSend(dht_queue, &tx_data, 0); // last arg determines time to wait; don't wait
}

void dht_init(){
    dht.setup(dht_pin, DHTesp::DHT11);

    dht_queue = xQueueCreate(SENSORQSIZE, DHTSIZE*sizeof(char));
    if (dht_queue == NULL){
        Serial.println("SENSOR QUEUE: error creating queue");
    }
}