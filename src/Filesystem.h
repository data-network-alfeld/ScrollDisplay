#pragma once
#include <Arduino.h>
#include <SPIFFS.h>
#include "Display.h"

extern String file_get_contents(String filename);
extern bool file_put_contents(String filename, String content);

extern void saveConfiguration();
extern void readConfiguration();
