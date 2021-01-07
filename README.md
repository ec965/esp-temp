# esp32 thermostat

## Todo
* additional leds
* iot control
* iot send temp
* iot get temp from online

## Documentation
2 tasks

### DHT 11 task
1. poll dht11
2. enqueue dht data
3. (to-do) handle isr from button to change what kind of data is enqueued

### display task
1. refresh 4digit7seg display
    1. uses timer interrupt to refresh display
2. dequeue dht data and display

## DHT11
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
