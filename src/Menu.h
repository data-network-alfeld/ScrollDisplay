#pragma once
#include <stdint.h>
#include <Arduino.h>
#include <Display.h>

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
	BACK,
	_MENUITEMS_LENGTH /* letzter Eintrag, als Limit */ 
};
extern const char* menuitemStrings[_MENUITEMS_LENGTH];
extern volatile uint8_t state; 
extern volatile uint8_t menuitem; 

extern void menuItemPressed();
