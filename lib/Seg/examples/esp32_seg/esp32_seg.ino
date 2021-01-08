#include <Arduino.h>
#include "Seg.h"

const uint8_t digit_pins[] = {26,27,14,12}; // digits
const uint8_t seg_pins[] = {21, 19, 18, 5, 17, 16, 4, 15}; // segments

FourDigitSevenSegment segdisp (digit_pins, seg_pins, COMMON_ANODE);


void setup(){
    Serial.begin(115200);
    segdisp.init();
}

void loop(){
    Serial.println("Showing 0 on digit zero");
    segdisp.d(0);
    segdisp.s('0');
    delay(1000);
    
    Serial.println("Showing 1 on digit one");
    segdisp.d(1);
    segdisp.s('1');
    delay(1000);
    
    Serial.println("Showing 2 on digit two");
    segdisp.d(2);
    segdisp.s('2');
    delay(1000);
    
    Serial.println("Showing 3 on digit three");
    segdisp.d(3);
    segdisp.s('3');
    delay(1000);
}