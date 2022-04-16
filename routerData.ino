#include <EEPROM.h>
#include "headers/routerData.h"
#include "headers/private.h"

RouterData getRouterData() {
	RouterData routerData;
	EEPROM.begin(sizeof(RouterData));
	delay(10);
	EEPROM.get(0, routerData);
	EEPROM.end();
	return routerData;
}

void setRouterData(RouterData& routerData) {
	EEPROM.begin(sizeof(RouterData));
	delay(10);
	EEPROM.put(0, routerData);
	EEPROM.commit();
	EEPROM.end();
}