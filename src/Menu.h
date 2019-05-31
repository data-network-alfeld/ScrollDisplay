#pragma once
#include <stdint.h>
#include <Arduino.h>
#include "Display.h"
#include "Encoder.h"
#include "Main.h"
#include "WLAN.h"
#include "FirmwareUpdate.h"
#include "Settings.h"

// Displayzustände
enum STATE {
	SCROLLTEXT, 
	TEMPERATURE, 
	CLOCK,
	CLOCKANDDATE,
	MENU, 
	_STATE_LENGTH /* letzter Eintrag, als Limit */ 
};

// Menueinträge
enum MENUITEMS {
	BRIGHTNESS, 
	WIFIMENU, 
	WIFIINFO,
	FIRMWAREUPDATE,
	ABOUT, 
	TEXT,
	UHR,
	UHRUNDDATUM,
	_MENUITEMS_LENGTH /* letzter Eintrag, als Limit */ 
};
extern const char* menuitemStrings[_MENUITEMS_LENGTH];
extern volatile uint8_t state; 
extern volatile uint8_t menuitem; 

extern void menuItemPressed(Encoder& enc);
