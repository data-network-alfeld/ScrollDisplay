#include <Menu.h>

const char* menuitemStrings[_MENUITEMS_LENGTH] = {
	"Helligkeit",
	"WLAN-Menü",
	"WLAN-Infos",
	"FW-Update",
	"Über...",
	"zurück"
};

volatile uint8_t state = MENU; 
volatile uint8_t menuitem = BRIGHTNESS; 

void menuItemPressed(Encoder& enc)
{
	Display& disp = Display::instance();
	switch (menuitem)
	{
		case MENUITEMS::BACK:
			state = SCROLLTEXT;
			enc.setLimits(0, 20, 5);
			break;
		case MENUITEMS::ABOUT:
			Serial.println("Written by Tobias Mädel <t.maedel@alfeld.de>");
			Serial.println("Visit Data Network Alfeld e.V. at https://dna-ev.de");
			disp.displayText("DNA Scrolldisplay   ", textPosition_t::PA_LEFT, 50, 2000, textEffect_t::PA_SCROLL_LEFT);
			disp.animateUntilButtonPress();
			disp.displayText("Written by Tobias Mädel  ", textPosition_t::PA_LEFT, 50, 2000, textEffect_t::PA_SCROLL_LEFT);
			disp.animateUntilButtonPress();
			disp.displayText("Kompiliert am" , textPosition_t::PA_LEFT, 50, 1000, textEffect_t::PA_MESH);
			disp.animateUntilButtonPress();
			disp.displayText(__DATE__, textPosition_t::PA_LEFT, 50, 2000, textEffect_t::PA_MESH);
			disp.animateUntilButtonPress();
			disp.displayText( __TIME__ , textPosition_t::PA_LEFT, 50, 1000, textEffect_t::PA_OPENING_CURSOR);
			disp.animateUntilButtonPress();

			break;
		case MENUITEMS::BRIGHTNESS:
			enc.setLimits(0, 15, disp.intensity);
			while (Encoder::buttonPressed == 0)
			{
				disp.intensity = enc.getCount();
				disp.displayText(String("Helligkeit - ") + String(disp.intensity), textPosition_t::PA_LEFT, 0, 0, textEffect_t::PA_PRINT);
				disp.parola.setIntensity(disp.intensity);
				disp.parola.displayAnimate();
			}
			Encoder::buttonPressed = 0;
			enc.setLimits(0, _MENUITEMS_LENGTH - 1);
			break; 
		case MENUITEMS::WIFIMENU:
			wm.startConfigPortal(ssid.c_str(), NULL);
			disp.displayText(ssid, textPosition_t::PA_LEFT, 50, 2000, textEffect_t::PA_SCROLL_LEFT);
			disp.animateUntilButtonPress();
			disp.displayText(ssid, textPosition_t::PA_LEFT, 0, 0, textEffect_t::PA_PRINT);
			disp.animateUntilButtonPress(true);
			break;
		case MENUITEMS::WIFIINFO:
			disp.displayText(WiFi.SSID(), textPosition_t::PA_LEFT, 50, 2000, textEffect_t::PA_MESH);
			disp.animateUntilButtonPress(false);
			disp.displayText(String("IP: ") + WiFi.localIP().toString() , textPosition_t::PA_RIGHT, 50, 5000, textEffect_t::PA_SCROLL_LEFT);
			disp.animateUntilButtonPress(false);
			break;
		case MENUITEMS::FIRMWAREUPDATE:
		{
			disp.displayText("Suche...", textPosition_t::PA_CENTER, 0, 500, textEffect_t::PA_PRINT);
			disp.animateUntilButtonPress();
			disp.displayText("nicht abschalt.", textPosition_t::PA_LEFT, 0, 0, textEffect_t::PA_PRINT);
			disp.animateUntilButtonPress();	
			uint8_t otaResult = tryOTAUpdate();
			switch (otaResult)
			{
				case OTAResult::SERVER_ERROR:
					disp.displayText("Serverfehler", textPosition_t::PA_CENTER, 0, 500, textEffect_t::PA_PRINT);
					disp.animateUntilButtonPress();
					disp.displayText(otaErrorCode, textPosition_t::PA_RIGHT, 100, 2500, textEffect_t::PA_SCROLL_LEFT);
					disp.animateUntilButtonPress();
					break;
				case OTAResult::NO_WIFI_CONNECTION:
					disp.displayText("Kein WLAN", textPosition_t::PA_CENTER, 0, 5000, textEffect_t::PA_PRINT);
					disp.animateUntilButtonPress();	
				case OTAResult::NO_UPDATE:
					disp.displayText("Kein Update", textPosition_t::PA_CENTER, 0, 5000, textEffect_t::PA_PRINT);
					disp.animateUntilButtonPress();	
				default:
					break;
			}
		}
			break;
		default:
			break;
	}
	disp.setDisplayState();
}