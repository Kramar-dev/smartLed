#pragma once

#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>

void webUpdateSetup();
const char* getUniqueWebUpdateHost();