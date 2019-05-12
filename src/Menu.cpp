#include <Menu.h>

const char* menuitemStrings[_MENUITEMS_LENGTH] = {
	"Helligkeit",
	"WLAN-Menü",
	"Infos",
	"zurück"
};

volatile uint8_t state = MENU; 
volatile uint8_t menuitem = BRIGHTNESS; 

