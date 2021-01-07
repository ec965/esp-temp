#include <Arduino.h>
#include "DHTesp.h"
#include "src/macros.h"
#include "src/display.h"
#include "src/timer.h"
#include "src/dht.h"
#include "src/bx.h"

void setup() {
    Serial.begin(115200);
    Serial.println("Init display");

    // display
    segdisp.init();
    timer_init();
    // dht11
    dht_init();
    // button
    bx_init();

    xTaskCreate(refresh_display, "refresh display", 1000, NULL, 1, NULL);
    xTaskCreate(poll_sensor, "dht 11 polling", 4000, NULL, 1, NULL);
    xTaskCreate(button_task, "button task", 1000, NULL, 1, NULL);
}

void loop() {
}
