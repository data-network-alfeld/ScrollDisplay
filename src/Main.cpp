#include "Main.h"

Clock clo;
Encoder enc; 
Display& disp = Display::instance();

void setup()
{
	// UART für Debugging
	Serial.begin(115200);

	// Konfiguration aus dem SPIFFS lesen
	beginConfiguration();
	readConfiguration();

	// Drehencoder initialisieren
	enc.attachSingleEdge(ENCODER_DT, ENCODER_CLK);
	enc.attachButton(ENCODER_SW);

	// Vernünftigen Ausgangszustand definieren
	state = STATE::SCROLLTEXT;
	enc.setLimits(0, 20, 5);

	// Display initialisieren
	disp.init(ENCODER_SW, enc, clo);

	disp.displayText("Bitte warten", textPosition_t::PA_LEFT, 1, 1000, PA_PRINT, PA_NO_EFFECT);
	disp.parola.displayAnimate();

	// WLAN initialisieren
	initWLAN();

	// Uhrzeit stellen
	if (WiFi.status() == WL_CONNECTED) {
		clo.init();
	}

	disp.setDisplayState();
}

void loop()
{
	wm.process();
	disp.render();
	delay(1);
}