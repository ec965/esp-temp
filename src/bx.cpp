#include <Arduino.h>
#include "bx.h"
#include "macros.h"

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
    bx_queue = xQueueCreate(QSIZE, sizeof(bool));
    if (bx_queue == NULL){
        Serial.println("Error creating the bx queue");
    }
}

void button_task(void* parameter){
    bool bx_pressed=false;
    uint32_t past_time = millis();

    while(1){
        xSemaphoreTake(bx_semaphore, portMAX_DELAY);

        // debounce 100ms
        if (millis() - past_time > 500){
            Serial.println("button was pressed");
            bx_pressed=true;
            xQueueSend(bx_queue, &bx_pressed, portMAX_DELAY);
            bx_pressed=false;        
            past_time = millis();
        }
    }
    vTaskDelete(NULL);
}