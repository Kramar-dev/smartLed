#include "headers/blink.h"

void blink(unsigned long time) {
	digitalWrite(D8, HIGH);
	delay(time);
	digitalWrite(D8, LOW);
};

void onConnectionBlinking() {
	for(int i = 0; i < 10; ++i) {
		blink(25);
		delay(100);
	}
};