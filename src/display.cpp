#include <Arduino.h>
#include <FdigSseg.h>
#include "display.h"
#include "timer.h"
#include "dht.h"
#include "config.h"

FdigSseg segdisp (digit_pins, seg_pins, COMMON_ANODE);

// refresh segdisp task
void display_task(void * parameter){
    DHT_DATA rx_data;

    while(1){
        xSemaphoreTake(tick_semaphore, portMAX_DELAY);

        if (xQueueReceive(dht_queue, &rx_data, 0) == pdTRUE){
            if (xSemaphoreTake(serial_semaphore, (TickType_t) 5) == pdTRUE){
                Serial.print("DISPLAY TASK:");
                Serial.print(rx_data.type);
                Serial.print("|");
                Serial.println(rx_data.str);
                xSemaphoreGive(serial_semaphore);
            }
        }
        segdisp.display_string(rx_data.str);
    }
    vTaskDelete(NULL);
}