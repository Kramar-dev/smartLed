#include <WebSocketsServer.h>
#include <ESP8266WiFi.h>
#include "header files/routerData.h"
#include "header files/blink.h"
#include "resources/html_page.h"

//#define LED 2
WebSocketsServer webSocketServer = WebSocketsServer(16251);
boolean LEDonoff = false;
String JSONtxt;
//====================================================================

void setup()
{
	RouterData routerData = getRouterData();
	
	Serial.begin(115200);
	pinMode(LED_BUILTIN, OUTPUT);
	//-----------------------------------------------
	WiFi.begin(routerData.ssid, routerData.password);
	while(WiFi.status() != WL_CONNECTED)
	{
		Serial.print(".");
		blink(25);
		delay(500);
	}
	WiFi.mode(WIFI_STA);
	Serial.println();
	Serial.print("Connected. Local IP: ");
	Serial.println(WiFi.localIP());
	onConnectionBlinking();
	//-----------------------------------------------
	//server.on("/", webpage);
	//-----------------------------------------------

	webSocketServer.begin();
	webSocketServer.onEvent(webSocketEvent);
}
//====================================================================

void loop()
{
	webSocketServer.loop();

	//-----------------------------------------------
	// if(LEDonoff == false) digitalWrite(LED, LOW);
	// else digitalWrite(LED, HIGH);
	//-----------------------------------------------
	//String LEDstatus = "OFF";
	//if(LEDonoff == true)
		//LEDstatus = "ON";
	//JSONtxt = "{\"LEDonoff\":\"" + LEDstatus + "\"}";
	//webSocket.broadcastTXT(JSONtxt);
}

//void webpage()
//{
	//server.send(200,"text/html", webpageCode);
//}
//=====================================================
//function process event: new data received from client
//=====================================================
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t welength)
{
	blink(25);
	String payloadString = (const char *)payload;
	//Serial.print("payloadString= ");
	Serial.println(payloadString);

	if(type == WStype_TEXT) //receive text from client
	{
		String sendData = "You said: " + payloadString;
		webSocketServer.broadcastTXT(sendData);
		/*byte separator = payloadString.indexOf('=');
		String var = payloadString.substring(0, separator);
		Serial.print("var= ");
		Serial.println(var);
		String val = payloadString.substring(separator+1);
		Serial.print("val= ");
		Serial.println(val);
		Serial.println(" ");

		if(var == "LEDonoff")
		{
			LEDonoff = false;
			if(val == "ON") LEDonoff = true;
		}*/
	}
}