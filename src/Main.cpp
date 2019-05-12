#include "Main.h"

Encoder enc; 
Display& disp = Display::instance();
WiFiManager wm;
String ssid; 

void setup()
{
	// UART für Debugging
	Serial.begin(115200);

	ssid = String("LED") + String(WIFI_getChipId(),HEX);

	wm.setClass("invert");
	wm.setConfigPortalBlocking(false);
	wm.setConfigPortalTimeout(300);

	if (wm.getWiFiIsSaved())
	{
		if(wm.autoConnect())
		{
			Serial.println("Connected!");
		}
		else
		{
			Serial.println("Connect failed :( ");
		}
	}
	
	// Drehencoder initialisieren
	enc.attachSingleEdge(ENCODER_DT, ENCODER_CLK);
	enc.attachButton(ENCODER_SW);

	// Vernünftigen Ausgangszustand definieren
	state = STATE::SCROLLTEXT;
	enc.setLimits(0, 20, 5);

	// Display initialisieren
	disp.init(ENCODER_SW, enc);
	disp.setDisplayState();
}

void loop()
{
	wm.process();
	disp.render();
	delay(1);
}

