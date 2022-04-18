#include "headers/blink.h"
#include "headers/defines.h"

Adafruit_NeoPixel signalLed(1, SIGNAL_LED_PIN, NEO_GRB + NEO_KHZ800);

void blink(uint8_t r, uint8_t g, uint8_t b) {
	setSignalLedColor(0x0, 0x0, 0x0);//digitalWrite(D8, HIGH);
	delay(25);
	setSignalLedColor(r, g, b);//digitalWrite(D8, LOW);
};

void setSignalLedColor(uint8_t r, uint8_t g, uint8_t b) {
	signalLed.clear();
	signalLed.setPixelColor(0, signalLed.Color(r, g, b));
	signalLed.show();
};
