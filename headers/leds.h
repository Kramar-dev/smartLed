#pragma once
#include <Adafruit_NeoPixel.h>
#include "defines.h"

#define LEDS_COUNT 5

#ifdef __AVR__
#include <avr/power.h>
#endif


void setColor(uint8_t& r, uint8_t& g, uint8_t& b);
