#pragma once

struct RouterData {
    char ssid[32];
    char password[32];
};

RouterData getRouterData();
void setRouterData(RouterData& routerData);
