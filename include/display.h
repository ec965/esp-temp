#pragma once
#include <Arduino.h>
#include <Seg.h>

class Display: public FourDigitSevenSegment {
    private:
        uint8_t digit_inc;
        uint8_t dot_counter;
        // helper function to show digits
        void show_digit(uint8_t digit, char c, bool period);
    public:
        Display(const uint8_t* d, const uint8_t* s, bool common);
        // parse and show dht data string
        void display_string(char* str);
};

extern Display segdisp;

// task to run segment display (varname: segdisp)
void display_task(void*);