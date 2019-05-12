#include <Menu.h>

const char* menuitemStrings[_MENUITEMS_LENGTH] = {
	"Helligkeit",
	"WLAN-Menü",
	"Infos",
	"zurück"
};

volatile uint8_t state = MENU; 
volatile uint8_t menuitem = BRIGHTNESS; 

void menuItemPressed()
{
	Display& disp = Display::instance();
	switch (menuitem)
	{
		case MENUITEMS::BACK:
			state = SCROLLTEXT;
			disp.setDisplayState();
			break;
		case MENUITEMS::ABOUT:
			Serial.println("Written by Tobias Mädel <t.maedel@alfeld.de>");
			Serial.println("Visit Data Network Alfeld e.V. at https://dna-ev.de");
			disp.displayText("DNA Scrolldisplay   ", textPosition_t::PA_LEFT, 50, 2000, textEffect_t::PA_SCROLL_LEFT);
			while (!disp.parola.displayAnimate()) {	delay(10);	}
			disp.displayText("Written by Tobias Mädel  ", textPosition_t::PA_LEFT, 50, 2000, textEffect_t::PA_SCROLL_LEFT);
			while (!disp.parola.displayAnimate()) {	delay(10);	}
			disp.setDisplayState();
			break;
		default:
			break;
	}
}