#pragma once
#include <Arduino.h>
#include <Preferences.h>
#include "Display.h"
#include "FirmwareUpdate.h"

extern void beginConfiguration(); 
extern void saveConfiguration();
extern void readConfiguration();
