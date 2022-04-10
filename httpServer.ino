#include <ESP8266WebServer.h>
#include "resources/mainPage.h"
#include "resources/savedSuccessfully.h"
#include "resources/dataIncorrect.h"
#include "headers/defines.h"
#include "headers/routerData.h"

ESP8266WebServer httpServer(80);

bool isCorrect(const char* data) {
    if (sizeof(data) > MAX_NAME_LEN || sizeof(data) == 0)
        return false;
    for(int i = 0; i < sizeof(data); ++i) 
        if (data[i] < 21 || data[i] > 125)
            return false;
    return true;
};

void handleHttpServer() {
    if (httpServer.method() == HTTP_POST) {
		const char* ssid = httpServer.arg("ssid").c_str();
		const char* password = httpServer.arg("password").c_str();
        RouterData routerData = {};
        strcpy(routerData.ssid, httpServer.arg("ssid").c_str());
        strcpy(routerData.password, httpServer.arg("password").c_str());
        if (isCorrect(ssid) && isCorrect(password)) {
            setRouterData(routerData);
            httpServer.send(200, HTML, saveSuccessfullyPage);
        }
        else
            httpServer.send(200, HTML, incorrectData);
	}
	else {
		httpServer.send(200, HTML, mainPage);

    }
}