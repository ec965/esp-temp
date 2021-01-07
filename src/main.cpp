#include <Arduino.h>
#include "DHTesp.h"
#include "config.h"
#include "display.h"
#include "timer.h"
#include "dht.h"
#include "bx.h"
#include "connect.h"

void setup() {
    Serial.begin(115200);
    Serial.println("Init display");
    // network (wifi & mqtt)
    network_init();
    // display
    segdisp.init();
    timer_init();
    // dht11
    dht_init();
    // button
    bx_init();

    xTaskCreate(mqtt_publisher, "mqtt publisher", 1000, NULL, 1, NULL);
    xTaskCreate(refresh_display, "refresh display", 1000, NULL, 1, NULL);
    xTaskCreate(poll_sensor, "dht 11 polling", 4000, NULL, 1, NULL);
    xTaskCreate(button_task, "button task", 1000, NULL, 1, NULL);
}

void loop() {
    vTaskDelay(portMAX_DELAY); // suspend the idle loop
}
