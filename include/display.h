#pragma once
#include <Arduino.h>
#include <FdigSseg.h>

extern FdigSseg segdisp;

// task to run segment display (varname: segdisp)
void display_task(void*);