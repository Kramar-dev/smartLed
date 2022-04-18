#include "ESP8266WiFi.h"
#include "headers/broadcast.h"
#include "headers/defines.h"
#include "headers/blink.h"
#include "headers/action.h"

char packetBuffer[PACKET_BUFFER];
uint8_t sendBuf[] = {0x44, 0x55, 0x50, 0x41}; //DUPA

WiFiUDP udp;

void parseBroadcast() {
	int parsedUdpPacket = udp.parsePacket();
	if (parsedUdpPacket) {
		blink(0x0, 0xFF, 0x0);  
		udp.read(packetBuffer, PACKET_BUFFER);
		udp.flush();
		
		if (String(packetBuffer) == BCAST_CHECK_MESSAGE) 
			onBcastMesageReceived();
	}
}

bool sendPacket(const IPAddress& address, const uint8_t* buf, uint8_t bufSize) {
  udp.beginPacket(address, BCAST_PORT);
  udp.write(buf, bufSize);
  return (udp.endPacket() == 1);
}

void onBcastMesageReceived() { //TODO: send by udp id info about current ESP32
	if (!sendPacket(udp.remoteIP(), sendBuf, sizeof(sendBuf)))
		Serial.println(F("Error sending broadcast UDP packet!"));
}