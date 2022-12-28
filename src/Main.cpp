#include "Main.h"
#include "esp_log.h"
#include "esp_wifi.h"

Clock clo;
Encoder enc; 
Display& disp = Display::instance();

void setup()
{
	// UART für Debugging
	Serial.begin(115200);

	esp_wifi_set_ps(WIFI_PS_NONE);

	esp_log_level_set("*", ESP_LOG_WARN);
	esp_log_level_set("wifi", ESP_LOG_DEBUG);
	esp_log_level_set("dhcpc", ESP_LOG_DEBUG);

	// Konfiguration aus dem SPIFFS lesen
	beginConfiguration();
	readConfiguration();

	// Drehencoder initialisieren
	enc.attachSingleEdge(ENCODER_DT, ENCODER_CLK);
	enc.attachButton(ENCODER_SW);

	// Vernünftigen Ausgangszustand definieren
	state = STATE::CLOCK;
	enc.setLimits(0, 20, 5);

	// Display initialisieren
	disp.init(ENCODER_SW, enc, clo);
	disp.parola->displayClear();
	
	disp.displayText("Bitte warten", textPosition_t::PA_LEFT, 1, 1000, PA_PRINT, PA_NO_EFFECT);
	disp.parola->displayAnimate();

	// WLAN initialisieren
	initWLAN();

	// Uhrzeit stellen
	if (WiFi.status() == WL_CONNECTED) {
		clo.init();
	}

	disp.setDisplayState();
}

uint32_t timeout = 0;
void loop()
{
	wm.process();
	disp.render();
	clo.process();

	delay(1);

	// Workaround for WiFi disconnection on Ubiquiti HW (reconnect/fw upgrades)
	if (millis() > timeout + 10000)
	{
		timeout = millis();
		/*Serial.print("WiFi.status(): ");
		Serial.println(WiFi.status());
		Serial.print("WiFi.localIP(): ");
		Serial.println(WiFi.localIP().toString());*/

		if (WiFi.status() == WL_DISCONNECTED)
		{
			Serial.println("WiFi disconnected. Trying to reconnect.");
			wm.autoConnect();
		}
	}
}
