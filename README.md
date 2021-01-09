# esp32 thermostat

![handsoldered_board](pics/board.jpg)

## Todo
* program leds according to comfort state
* wifi manager for setting up mqtt
* calibrate DHT11

## Tasks
### sensor task
* poll dht11
* send sensor data to display task
* send sensor data to mqtt publishing task
* check button queue

### display task
* refresh 4digit7seg display using hardware timer interrupt
* dequeue dht data and display

### button task
* wait for button isr
* if button pressed, send message via queue to sensor task to change data being send to display task

*_(bx = button)_

### MQTT task
* recieve messages via callback
    * enqueue messages to sensor task to change data being displayed on display task
* reconnect
* manage mqtt publishing message queue

## Queues
* dht_queue: SENSOR TASK -> DISPLAY TASK
    - used to send data to display
* bx_queue: BX TASK -> SENSOR_TASK
    - MQTT TASK -> SENSOR TASK
    - used to change what data type is being sent to display
* mqtt_pub_queue: SENSOR TASK -> MQTT TASK
    - used to publish sensor data over MQTT


## Libraries
* Seg: 4 digit 7 segement library built for this project.
* [WiFiManager](https://github.com/tzapu/WiFiManager): AP mode for WiFi management
    + Manually installed due to platformio error.
* [DHTesp](https://github.com/beegee-tokyo/DHTesp): DHT11 library for ESP32 which blocks interrupts when polling sensor.
* [PubSubClient](https://github.com/knolleary/pubsubclient/): MQTT publishing and subscribing


# DHT11
* response time: 6s min, 10s typical, 15s max
### humidity
characteristic | spec
----- | -----
range | 20-90% RH
tolerance | +- 5%
### temp
characteristic | spec
----- | -----
range | 0-50 degC
tolerance | +- 2 degC

## resources
* [4 digit 7 segment display](https://osoyoo.com/2017/08/08/arduino-lesson-4-digit-7-segment-led-display/)
* [dht 11 esp lib](https://github.com/beegee-tokyo/DHTesp)

### mosquitto cheat sheet
* Publish: mosquitto_pub -h <ipaddress> -m "<message>" -t <topic>
* Subscribe: mosquitto_sub -h <ipaddress> -t <topic>

__#__ is a wild card.
