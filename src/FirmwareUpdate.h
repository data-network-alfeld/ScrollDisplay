#pragma once

#include <Arduino.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include "FS.h"
#include "SPIFFS.h"
#include <MD5Builder.h>

#include <time.h>

extern uint8_t tryOTAUpdate();
//extern void setClock();

extern String otaErrorCode; 
extern uint8_t firmwareauswahl;

enum OTAResult {
	NO_WIFI_CONNECTION,
    NO_UPDATE,
    UPDATING,
    SERVER_ERROR
};