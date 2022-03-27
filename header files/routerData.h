#pragma once

struct RouterData {
    const char* ssid;
    const char* password;
};

RouterData getRouterData();
