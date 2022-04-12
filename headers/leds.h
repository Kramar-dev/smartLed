#pragma once
#include "defines.h"

#if DEVICE == DEVICE_MODE_LEDS
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define LEDS_COUNT 5

void setColor(uint8_t& r, uint8_t& g, uint8_t& b);
#endif