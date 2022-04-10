#include "headers/defines.h"
#include "headers/action.h"

void doAction(Action action) {
    switch(action) {
    
    CHANGE_COLOR:
        onChangeColor();
    break;
    
    GET_TEMP:
    break;
        onGetTemperature();
    default:
        //TODO sendding "unknown action" through websockets
    break;
    
    }
}

void onChangeColor() {
    //TODO Serial.println("changing color");
}

void onGetTemperature() {
    //TODO Serial.println("sending temp through websockets");
}