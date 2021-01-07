#include <Arduino.h>
#include "src/display.h"
#include "src/timer.h"
#include "src/dht.h"
#include "DHTesp.h"

void setup() {
    Serial.begin(115200);
    Serial.println("Init display");

    segdisp.init();
    dht.setup(dht_pin, DHTesp::DHT11); 
    timer_init();
    dht_queue = xQueueCreate( 1, DHTQSIZE*sizeof(char) );
 
    if(dht_queue == NULL){
        Serial.println("Error creating the queue");
    }

    xTaskCreate(refresh_display, "refresh display", 1000, NULL, 1, NULL);
    xTaskCreate(poll_sensor, "dht 11 polling", 4000, NULL, 1, NULL);
}

void loop() {
}
