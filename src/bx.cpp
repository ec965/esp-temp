#include <Arduino.h>
#include "bx.h"
#include "config.h"

//Queue button task to dht task
QueueHandle_t bx_queue;
// button interrupt semaphore
SemaphoreHandle_t bx_semaphore = xSemaphoreCreateBinary();

// button interrupt callback
void IRAM_ATTR onBxPress(){
    xSemaphoreGiveFromISR(bx_semaphore, NULL);
}

void bx_init(){
    // init the pin and attach interrupt
    pinMode(bx_pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(bx_pin), onBxPress, RISING);

    // init the bx_queue
    bx_queue = xQueueCreate(BXQSIZE, sizeof(uint8_t));
    if (bx_queue == NULL){
        Serial.println("BX QUEUE: error creating queue");
    }
}

void bx_task(void* parameter){
    uint8_t bx_pressed=TEMPC;
    uint32_t past_time = millis();

    while(1){
        xSemaphoreTake(bx_semaphore, portMAX_DELAY);

        // debounce 100ms
        if (millis() - past_time > 500){
            SERIALTAKE
            Serial.println("BX TASK: button was pressed");
            SERIALGIVE
            bx_pressed = change_data_type(bx_pressed);
            xQueueSend(bx_queue, &bx_pressed, portMAX_DELAY);
            past_time = millis();
        }
    }
    vTaskDelete(NULL);
}

uint8_t change_data_type(uint8_t data_type){
    SERIALTAKE
    Serial.print("BX TASK -> SENSOR TASK:");
    switch(data_type){
        case(TEMPC):
            Serial.println("HUMI(1)");
            data_type = HUMI;
            break;
        case(HUMI):
            Serial.println("TEMPF(2)");
            data_type = TEMPF;
            break;
        case(TEMPF):
            Serial.println("TEMPC(0)");
            data_type = TEMPC;
            break;
    }
    SERIALGIVE
    return data_type;
}