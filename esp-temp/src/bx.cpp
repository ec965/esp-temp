#include <Arduino.h>
#include "bx.h"
#include "macros.h"

//Queue button task to dht task
QueueHandle_t bx_queue;
// button interrupt semaphore
SemaphoreHandle_t bx_semaphore = xSemaphoreCreateBinary();

bool bx_pressed;

// button interrupt callback
void IRAM_ATTR onBxPress(){
    xSemaphoreGiveFromISR(bx_semaphore, NULL);
    Serial.println("button was pressed");
}

void bx_init(){
    // init the pin and attach interrupt
    pinMode(bx_pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(bx_pin), onBxPress, FALLING);

    // init the bx_queue
    bx_queue = xQueueCreate(QSIZE, sizeof(bool));
    if (bx_queue == NULL){
        Serial.println("Error creating the bx queue");
    }
}

void button_task(void* parameter){
    bx_pressed=false;
    while(1){
        xSemaphoreTake(bx_semaphore, portMAX_DELAY);
        bx_pressed=true;
        xQueueSend(bx_queue, &bx_pressed, portMAX_DELAY);
        bx_pressed=false;        
    }
    vTaskDelete(NULL);
}