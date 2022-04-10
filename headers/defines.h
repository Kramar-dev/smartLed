#pragma once

#define BCAST_PORT 16250
#define PACKET_BUFFER 5
#define BCAST_CHECK_MESSAGE "ESP32"
#define HTML "text/html"
#define MAX_NAME_LEN 64
#define SOFT_AP_NAME "ESP32"
#define SOFT_AP_PASSWORD "12345678"
#define MODE_PIN D1


enum Mode {
    CONFIG,
    WORK
};