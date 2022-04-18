#include "headers\webupdate.h"
#include "headers\httpServer.h"
#include "headers\defines.h"

ESP8266HTTPUpdateServer httpUpdater;
extern ESP8266WebServer httpServer;

void webUpdateSetup() {
	MDNS.begin(WEBUPDATE_HOST/*getUniqueWebUpdateHost()*/); //TODO
	httpUpdater.setup(&httpServer);
	httpServer.begin();
	MDNS.addService("http", "tcp", WEBUPDATE_PORT);
}

const char* getUniqueWebUpdateHost() {
	const char* a;
	return a;
}