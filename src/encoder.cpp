#include "encoder.h"

void encoderInit()
{
    pinMode(ENCODER_CLK, INPUT); 
	digitalWrite(ENCODER_CLK, HIGH); 
	pinMode(ENCODER_DT, INPUT); 
	digitalWrite(ENCODER_DT, HIGH); 
}

void IRAM_ATTR encoderChange()
{
	
}
