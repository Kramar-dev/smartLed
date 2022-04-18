#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include "headers/routerData.h"
#include "headers/blink.h"
#include "headers/broadcast.h"
#include "headers/defines.h"
#include "headers/httpServer.h"
#include "headers/mode.h"
#include "headers/action.h"
#include "headers/running.h"
#include "headers/leds.h"
#include "headers/tempSensor.h"

extern WiFiUDP udp;
extern ESP8266WebServer httpServer;
extern Running running;
extern Adafruit_NeoPixel signalLed;
extern Adafruit_BMP280 bmp;

uint8_t mode;
WebSocketsServer webSocketServer = WebSocketsServer(16251);

#if DEVICE == DEVICE_MODE_LEDS
extern Adafruit_NeoPixel addressedLeds;
#endif

//############################################################################################

void setup() {
	Serial.begin(115200);
	//pinMode(D8, OUTPUT);
	pinMode(MODE_PIN, INPUT_PULLUP);
	mode = getMode();
	#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
		clock_prescale_set(clock_div_1);
	#endif
	signalLed.begin();


	if (mode == WORK) {
		setSignalLedColor(0xFF, 0x0, 0x0);
		httpServer.close();
		RouterData routerData = getRouterData();
		WiFi.begin(routerData.ssid, routerData.password);
		Serial.println();
		while(WiFi.status() != WL_CONNECTED)
		{
			Serial.print(".");
			delay(500);
		}
		setSignalLedColor(0x0, 0xFF, 0x0);//onConnectionBlinking();
		WiFi.mode(WIFI_STA);
		Serial.print("\nConnected. Local IP: ");
		Serial.print(WiFi.localIP());
		Serial.print("\nBroadcast IP: ");
		Serial.print(WiFi.broadcastIP());
		Serial.println("\nStarting UDP...");
		udp.begin(BCAST_PORT);
		Serial.print("Broadcast port: ");
		Serial.print(udp.localPort());
		Serial.println();
		webSocketServer.begin(); //TODO open websocket only if any esp will answer through udp
		webSocketServer.onEvent(webSocketEvent);
		//#if DEVICE == DEVICE_MODE_LEDS
		//#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
			//clock_prescale_set(clock_div_1);
		//#endif
			addressedLeds.begin();
		//#endif

		#if DEVICE == DEVICE_MODE_TEMP
		if (!bmp.begin(0x76)) {
			Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
						"try a different address!"));
			while (1) delay(10);

  		bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
						Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
						Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
						Adafruit_BMP280::FILTER_X16,      /* Filtering. */
						Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
  		}
		
		#endif

	}
	else if (mode == CONFIG) {
		setSignalLedColor(0x0, 0x0, 0xFF);
		webSocketServer.close();
		WiFi.mode(WIFI_AP);
		WiFi.softAP(SOFT_AP_NAME, SOFT_AP_PASSWORD);
		httpServer.on("/",  handleHttpServer);
		httpServer.begin();
		Serial.println();
		Serial.println("AP started");
		//onConnectionBlinking();
	}

};

//############################################################################################

void loop() {
		switch (mode) {
		case CONFIG:
			httpServer.handleClient();
			break;
		
		case WORK:
			if (WiFi.status() == WL_CONNECTED)
				setSignalLedColor(0x0, 0xff, 0x0);
			else
				setSignalLedColor(0xff, 0x0, 0x0);
			
			parseBroadcast();
			webSocketServer.loop();
			if (running.sendingTemp) {
				onGetTemperature();
				delay(500);
			}
			break;
		}
		delay(1);
};

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t welength) {
	blink(0x0, 0xFF, 0x0);
	
	doAction(payload, welength);

	String payloadString = (const char *)payload;
	if(type == WStype_TEXT) {
		String sendData = "You said: " + payloadString;
		webSocketServer.broadcastTXT(sendData);
	}
};