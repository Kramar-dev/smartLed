#include "header files/blink.h"

void blink(int time) {
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