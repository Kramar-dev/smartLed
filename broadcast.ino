#include "header files/broadcast.h"
#include "header files/defines.h"
#include "header files/blink.h"

char packetBuffer[PACKET_BUFFER];
uint8_t sendBuf[] = {0x44, 0x55, 0x50, 0x41}; //DUPA

WiFiUDP udp;
IPAddress broadcastAddress;

void parseBroadcast() {
    int parsedUdpPacket = udp.parsePacket();
    if (parsedUdpPacket) {
        blink(25);  
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

void setBroadcastIp() {
    broadcastAddress = (uint32_t)WiFi.localIP() | ~((uint32_t)WiFi.subnetMask());
}

void onBcastMesageReceived() { //TODO
    if (!sendPacket(udp.remoteIP(), sendBuf, sizeof(sendBuf)))
        Serial.println(F("Error sending broadcast UDP packet!"));
}