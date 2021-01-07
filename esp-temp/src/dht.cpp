#include <Arduino.h>
#include "DHTesp.h"
#include "dht.h"
#include "macros.h"
#include "bx.h"

// Queue from dht task to display task
QueueHandle_t dht_queue;
DHTesp dht;
uint8_t data_type; // what kind of data are we sending? Celcius, Farenheit, or Humidity

void poll_sensor(void* parameter){
    uint8_t data_type = TEMPC;
    TempAndHumidity prev_data;
    prev_data.temperature = 0;
    prev_data.humidity = 0;
    
    vTaskDelay(1000 / portTICK_PERIOD_MS); //give the sensor some time to start up

    while(1){
        // poll DHT11 and update temperature
        TempAndHumidity data = dht.getTempAndHumidity();
        if (dht.getStatus() != 0){
            Serial.println("failed to get dht data");
       } else {
            Serial.print("Temp: ");
            Serial.print(data.temperature);
            Serial.print(" | Humi: ");
            Serial.println(data.humidity);

            enqueue_dht_data(data);

            prev_data = data;
        } 
        
        // handle button presses
        bool bx_queue_item;
        // uses queue timer as a delay
        if (xQueueReceive(bx_queue, &bx_queue_item, 10000 / portTICK_PERIOD_MS) == pdTRUE){
            change_data_type();
            enqueue_dht_data(prev_data);
        }
    }
    vTaskDelete(NULL);
}

void enqueue_dht_data(TempAndHumidity data){
    DHT_DATA tx_data; //struct to hold tx data
    
    switch (data_type){
        case(TEMPC):
            sprintf(tx_data.str, "%.*fc\0", 1, data.temperature);
            tx_data.type=TEMPC;
            break;            
        case(HUMI):
            sprintf(tx_data.str, "%.*fh\0", 1, data.humidity);
            tx_data.type=HUMI;
            break;            
        case(TEMPF):
            float tempf = (data.temperature * 1.8) + 32;
            sprintf(tx_data.str, "%.*ff\0", 1, tempf);
            tx_data.type=TEMPF;
            break;
    }
    Serial.print("dht task sending:");
    Serial.print(tx_data.type);
    Serial.print("|");
    Serial.println(tx_data.str);

    xQueueSend(dht_queue, &tx_data, 0); // last arg determines time to wait; don't wait
}

void dht_init(){
    dht.setup(dht_pin, DHTesp::DHT11);

    dht_queue = xQueueCreate(QSIZE, DHTSIZE*sizeof(char));
    if (dht_queue == NULL){
        Serial.println("Error creating the dht queue");
    }
}

void change_data_type(){
    switch(data_type){
        case(TEMPC):
            Serial.println("dht task will now send HUMI (1) to display task");
            data_type = HUMI;
            break;
        case(HUMI):
            Serial.println("dht task will now send TEMPF (2) to display task");
            data_type = TEMPF;
            break;
        case(TEMPF):
            Serial.println("dht task will now send TEMPC (0) to display task");
            data_type = TEMPC;
            break;
    }
}
