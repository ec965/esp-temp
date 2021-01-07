#pragma once
#include <Arduino.h>
#include "lib/seg.h"

extern FourDigitSevenSegment segdisp;

void refresh_display(void*);

void show_digit(uint8_t digit, char c, bool period);
