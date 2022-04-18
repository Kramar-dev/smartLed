#pragma once

#define BCAST_PORT 16250
#define PACKET_BUFFER 5
#define BCAST_CHECK_MESSAGE "ESP32"
#define HTML "text/html"
#define MAX_NAME_LEN 64
#define SOFT_AP_NAME "ESP32"
#define SOFT_AP_PASSWORD "12345678"
#define MODE_PIN D1
#define LED_STRIP_PIN D0//D2 - LED_BUILTIN
#define SIGNAL_LED_PIN D8

#define WEBUPDATE_HOST "esp32-webupdate" //TODO get unique host
#define WEBUPDATE_PORT 80

#define DEVICE_MODE_LEDS 0x10
#define DEVICE_MODE_TEMP 0x11

#define DEVICE DEVICE_MODE_LEDS


enum Mode {
	CONFIG,
	WORK
};

enum Action {
	CHANGE_COLOR = 0x10,
	START_GET_TEMP,
	STOP_GET_TEMP
};