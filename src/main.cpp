#include <Arduino.h>

#include "configuration.h"
#include "Encoder.h"
#include "menu.h"
#include "Display.h"

Encoder enc; 
Display disp; 

void setup()
{
	// UART für Debugging
	Serial.begin(115200);
	
	// Drehencoder initialisieren
	enc.attachSingleEdge(ENCODER_DT, ENCODER_CLK);
	enc.setLimits(0, _MENUITEMS_LENGTH - 1);

	// Display initialisieren
	disp.init(ENCODER_SW);
	disp.setDisplayState();
}

void loop()
{
	if (enc.getEncoderChanged())
	{
		Serial.println(enc.getCount());

		menuitem = enc.getCount();
		disp.setDisplayState();
	}
 
	disp.render();
	delay(100);
}

