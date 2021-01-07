#pragma once
#include <Arduino.h>
#include "lib/seg.h"

extern FourDigitSevenSegment segdisp;

// task to run segment display (varname: segdisp)
void refresh_display(void*);

// helper function to show digits
void show_digit(uint8_t digit, char c, bool period);
