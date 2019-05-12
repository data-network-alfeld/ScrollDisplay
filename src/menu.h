#pragma once
#include <stdint.h>

// Displayzustände
enum STATE {
	SCROLLTEXT, 
	TEMPERATURE, 
	MENU, 
	_STATE_LENGTH /* letzter Eintrag, als Limit */ 
};

// Menueinträge
enum MENUITEMS {
	BRIGHTNESS, 
	WIFIMENU, 
	ABOUT, 
	_MENUITEMS_LENGTH /* letzter Eintrag, als Limit */ 
};
const char* menuitemStrings[_MENUITEMS_LENGTH] = {
	"Helligkeit",
	"WLAN-Men\x81",
	"Infos"
};

volatile uint8_t state = MENU; 
volatile uint8_t menuitem = BRIGHTNESS; 

