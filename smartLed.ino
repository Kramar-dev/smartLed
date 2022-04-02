#include <WebSocketsServer.h>
#include <ESP8266WiFi.h>

//#include <AsyncUDP.h>

#include "header files/routerData.h"
#include "header files/blink.h"
#include "header files/broadcast.h"
#include "header files/defines.h"
#include "resources/html_page.h"


WebSocketsServer webSocketServer = WebSocketsServer(16251);
//String JSONtxt;
extern WiFiUDP udp;
extern IPAddress broadcastAddress;
//====================================================================

void setup()
{
	Serial.begin(115200);
	RouterData routerData = getRouterData();
	
	pinMode(LED_BUILTIN, OUTPUT);
	//-----------------------------------------------
	WiFi.begin(routerData.ssid, routerData.password);
	Serial.println();
	while(WiFi.status() != WL_CONNECTED)
	{
		Serial.print(".");
		blink(25);
		delay(500);
	}
	WiFi.mode(WIFI_STA);
	Serial.print("\nConnected. Local IP: ");
	Serial.print(WiFi.localIP());
	Serial.print("\nBroadcast IP: ");
	Serial.print(WiFi.broadcastIP());

	onConnectionBlinking();
	//-----------------------------------------------
	//server.on("/", webpage);
	//-----------------------------------------------

	Serial.println("\nStarting UDP...");
	udp.begin(BCAST_PORT);
	Serial.print("Broadcast port: ");
	Serial.print(udp.localPort());
	Serial.println();
	webSocketServer.begin();
	webSocketServer.onEvent(webSocketEvent);
	setBroadcastIp();
}
//====================================================================

void loop()
{
	parseBroadcast();
	webSocketServer.loop();
	delay(1);
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