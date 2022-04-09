#pragma once

#include <WiFiUdp.h>

void parseBroadcast();
bool sendPacket(const IPAddress& address, const uint8_t* buf, uint8_t bufSize);
void setBroadcastIp();
void onBcastMesageReceived();