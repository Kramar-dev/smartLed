#include "headers/routerData.h"
#include "headers/private.h"

RouterData getRouterData() {
    RouterData routerData;
    routerData.ssid = ssid; //ssid = "router ssid"
    routerData.password = password; //password = "router password"
    return routerData;
}