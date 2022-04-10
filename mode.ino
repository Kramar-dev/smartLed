#include "headers/defines.h"

Mode getMode() {
    if(digitalRead(MODE_PIN) == 0)
        return CONFIG;
    else
        return WORK;
}