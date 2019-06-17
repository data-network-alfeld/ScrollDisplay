#pragma once

#include <WiFiManager.h> 
#include "Display.h"
#include "Settings.h"
#include "Sprite.h"
#include "Clock.h"
#include "FirmwareUpdate.h"

extern WiFiManager wm;
extern WiFiManagerParameter custom_field;
extern String ssid;
extern Clock clo;

extern void initWLAN();