#include "header files/routerData.h"
#include "header files/private.h"

RouterData getRouterData() {
    RouterData routerData;
    routerData.ssid = ssid; //ssid = "router ssid"
    routerData.password = password; //password = "router password"
    return routerData;
}