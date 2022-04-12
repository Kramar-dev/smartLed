#include "headers/defines.h"
#include "headers/action.h"
#include "headers/leds.h"

#if DEVICE == DEVICE_MODE_LEDS
extern Adafruit_NeoPixel addressedLeds;
#endif

void doAction(uint8_t *payload) {
    Action action = Action(payload[sizeof(SOFT_AP_NAME)]);

    switch(action) {
    
    #if DEVICE == DEVICE_MODE_LEDS
    case CHANGE_COLOR:
        onChangeColor(payload[6], payload[7], payload[8]);
    break;
    #endif
    
    #if DEVICE == DEVICE_MODE_TEMP
    case GET_TEMP:
        onGetTemperature();
    break;
    #endif
    
    default:
        //TODO sendding "unknown action" through websockets
    break;
    
    }
}

void onChangeColor(uint8_t& r, uint8_t& g, uint8_t& b) {
    addressedLeds.clear();
    setColor(r, g, b);
}

void onGetTemperature() {
    //TODO Serial.println("sending temp through websockets");
}