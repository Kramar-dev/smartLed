#include <WebSocketsServer.h>
#include "headers/defines.h"
#include "headers/action.h"

#if DEVICE == DEVICE_MODE_LEDS
#include "headers/leds.h"
extern Adafruit_NeoPixel addressedLeds;
#endif

#if DEVICE == DEVICE_MODE_TEMP
#include "headers/tempSensor.h"
#include "headers/running.h"
extern Adafruit_BMP280 bmp;
extern Running running;
#endif


extern WebSocketsServer webSocketServer;

void doAction(uint8_t *payload, size_t& welength) {
    Action action = Action(payload[sizeof(SOFT_AP_NAME)-1]);
    
    switch(action) {
    
    #if DEVICE == DEVICE_MODE_LEDS
    case CHANGE_COLOR:
        uint8_t colorIndex = sizeof(SOFT_AP_NAME);
        onChangeColor(payload[colorIndex], payload[colorIndex+1], payload[colorIndex+2]);
    break;
    #endif
    
    #if DEVICE == DEVICE_MODE_TEMP
    case START_GET_TEMP:
        running.sendingTemp = true;
        onGetTemperature();
    break;

    case STOP_GET_TEMP:
        running.sendingTemp = false;
    break;
    #endif
    }
}

void onChangeColor(uint8_t& r, uint8_t& g, uint8_t& b) {
    #if DEVICE == DEVICE_MODE_LEDS
    addressedLeds.clear();
    setColor(r, g, b);
    #endif
}

void onGetTemperature() {
    #if DEVICE == DEVICE_MODE_TEMP
    float temp = bmp.readTemperature();
    float pressure = bmp.readPressure();
    float altitude = bmp.readAltitude(1013.25);/* Adjusted to local forecast! */
    String info = String(temp) + ";" + String(pressure) + ";" + String(altitude);
    webSocketServer.broadcastTXT(info);
    #endif
}