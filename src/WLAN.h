#pragma once

#include <WiFiManager.h> 
#include "Display.h"
#include "Settings.h"

extern WiFiManager wm;
extern WiFiManagerParameter custom_field;
extern String ssid;

extern void initWLAN();