#pragma once

#include <WiFiManager.h> 
#include "Display.h"
#include "Settings.h"
#include "Sprite.h"

extern WiFiManager wm;
extern WiFiManagerParameter custom_field;
extern String ssid;

extern void initWLAN();