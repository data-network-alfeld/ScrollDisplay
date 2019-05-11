#pragma once
#include <Arduino.h>
#include "configuration.h"

void encoderInit();
void IRAM_ATTR encoderChange();