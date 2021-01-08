# esp32 thermostat

## Todo
* additional leds or blink onboard led? or both?
* wifi manager for setting up wifi and mqtt
* front end for mqtt?
* iot get temp from online

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

### MQTT task
* recieve messages via callback
* reconnect
* manage mqtt publishing message queue

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
