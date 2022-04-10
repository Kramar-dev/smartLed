
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include "headers/routerData.h"
#include "headers/blink.h"
#include "headers/broadcast.h"
#include "headers/defines.h"
#include "headers/httpServer.h"
#include "headers/mode.h"


extern WiFiUDP udp;
extern IPAddress broadcastAddress;
extern ESP8266WebServer httpServer;
uint8_t mode;
WebSocketsServer webSocketServer = WebSocketsServer(16251);

//====================================================================

void setup() {
	Serial.begin(115200);
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(MODE_PIN, INPUT_PULLUP);
	mode = getMode();
	
	if (mode == WORK) {
		httpServer.close();
		RouterData routerData = getRouterData();
		WiFi.begin(routerData.ssid, routerData.password);
		Serial.println();
		while(WiFi.status() != WL_CONNECTED)
		{
			Serial.print(".");
			blink(25);
			delay(500);
		}
		WiFi.mode(WIFI_STA);
		Serial.print("\nConnected. Local IP: ");
		Serial.print(WiFi.localIP());
		Serial.print("\nBroadcast IP: ");
		Serial.print(WiFi.broadcastIP());
		onConnectionBlinking();
		Serial.println("\nStarting UDP...");
		udp.begin(BCAST_PORT);
		Serial.print("Broadcast port: ");
		Serial.print(udp.localPort());
		Serial.println();
		webSocketServer.begin();
		webSocketServer.onEvent(webSocketEvent);
		setBroadcastIp();
	}
	else if (mode == CONFIG) {
		webSocketServer.close();
		WiFi.mode(WIFI_AP);
		WiFi.softAP(SOFT_AP_NAME, SOFT_AP_PASSWORD);
		httpServer.on("/",  handleHttpServer);
		httpServer.begin();
		Serial.println();
		Serial.println("AP started");
		onConnectionBlinking();
	}

}
//====================================================================

void loop() {
	switch (mode) {
	case CONFIG:
		httpServer.handleClient();
		break;
	
	case WORK:
		parseBroadcast();
		webSocketServer.loop();
		//webSocket.broadcastTXT(JSONtxt);
		break;
	default:
		break;
	}
	delay(1);
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t welength) {
	blink(25);
	String payloadString = (const char *)payload;
	if(type == WStype_TEXT) {
		String sendData = "You said: " + payloadString;
		webSocketServer.broadcastTXT(sendData);
	}
}