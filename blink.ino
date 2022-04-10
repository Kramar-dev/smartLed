#include "headers/blink.h"

void blink(unsigned long time) {
  digitalWrite(LED_BUILTIN, LOW);
  delay(time);
  digitalWrite(LED_BUILTIN, HIGH);
};

void onConnectionBlinking() {
    for(int i = 0; i < 6; ++i) {
        blink(25);
        delay(300);
    }
};