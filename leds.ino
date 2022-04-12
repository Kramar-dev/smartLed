#include "headers/leds.h"
#if DEVICE == DEVICE_MODE_LEDS
Adafruit_NeoPixel addressedLeds(LEDS_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setColor(uint8_t& r, uint8_t& g, uint8_t& b) {
	for(int i = 0; i < LEDS_COUNT; ++i)
	{
		addressedLeds.setPixelColor(i, addressedLeds.Color(r, g, b));
		addressedLeds.show();
	}
}

#endif