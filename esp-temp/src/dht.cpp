#include <Arduino.h>
#include "DHTesp.h"
#include "dht.h"

QueueHandle_t dht_queue;
DHTesp dht;
const int dht_pin=25;

void poll_sensor(void* parameter){
    while(1){
        TempAndHumidity data = dht.getTempAndHumidity();
        if (dht.getStatus() != 0){
            Serial.println("failed to get dht data");
            vTaskDelay(6000 / portTICK_PERIOD_MS);
            // min time is 6 sec, if failed, try agian
       } else {
            Serial.print("Temp: ");
            Serial.print(data.temperature);
            Serial.print(" | Humi: ");
            Serial.println(data.humidity);

            uint8_t data_type = TEMPC; // what kind of data are we sending? Celcius, Farenheit, or Humidity

            DHT_DATA tx_data; //struct to hold tx data
            
            Serial.print("dht task sending:");
            switch (data_type){
                case(TEMPC):
                    sprintf(tx_data.str, "%.*fc", 1, data.temperature);
                    tx_data.type=TEMPC;
                    Serial.print(tx_data.type);
                    Serial.print("|");
                    Serial.println(tx_data.str);
                    break;            
            }

            xQueueSend(dht_queue, &tx_data, 0);
            vTaskDelay(15000 / portTICK_PERIOD_MS); // typical response time is 10sec
            // 15 sec gives the least amount of errors.
        } 
    }
    vTaskDelete(NULL);
}

void dht_queue_init(){
    dht_queue = xQueueCreate(5, 5*sizeof(char));
    if (dht_queue == NULL){
        Serial.println("Error creating the queue");
        while(1);
    }
}
