#include <Arduino.h>
#include <DHTesp.h>
#include <WiFiManager.h>
#include "config.h"
#include "display.h"
#include "timer.h"
#include "dht.h"
#include "bx.h"
#include "connect.h"
#include "led.h"

void setup() {
    Serial.begin(115200);
    Serial.println("Initializing...");
    
    pinMode(onboardled_pin, OUTPUT);
    digitalWrite(onboardled_pin, HIGH);

    // pinMode(redled_pin, OUTPUT);
    // pinMode(greenled_pin, OUTPUT);
    // pinMode(blueled_pin, OUTPUT);
    // digitalWrite(redled_pin, HIGH);
    // digitalWrite(blueled_pin, HIGH);
    // digitalWrite(greenled_pin, HIGH);

    // setup wifi
    WiFi.mode(WIFI_STA);
    WiFiManager wm;
    // wm.resetSettings(); // to reset saved wifi
    bool res;
    res = wm.autoConnect(mqtt_client_id, "password");

    if (!res){
        Serial.println("failed to connect to wifi");
    } else {
        Serial.println("wifi connected");
        digitalWrite(onboardled_pin, LOW);
        mqtt_init();
        xTaskCreate(mqtt_pub_task, "mqtt publisher", 4000, NULL, 1, NULL);
    }

    // display
    segdisp.init();
    timer_init();
    // dht11
    dht_init();
    // button
    bx_init();

    xTaskCreate(display_task, "refresh display", 4000, NULL, 1, NULL);
    xTaskCreate(sensor_task, "dht 11 polling", 4000, NULL, 1, NULL);
    xTaskCreate(bx_task, "button task", 4000, NULL, 1, NULL);
}

void loop() {
}
