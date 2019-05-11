#include "encoder.h"

// Encoder routines based on AiEsp32RotaryEncoder by igorantolic
volatile int16_t encoderValue = 0;
portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

uint8_t old_AB;
int16_t _minEncoderValue = 0;
int16_t _maxEncoderValue = 50;
bool _circleValues = false; 
int8_t enc_states[16] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
volatile int16_t encoder0Pos = 0;

void encoderInit()
{
    pinMode(ENCODER_CLK, INPUT_PULLUP); 
    pinMode(ENCODER_DT, INPUT_PULLUP); 

    attachInterrupt(ENCODER_CLK, encoderChange, CHANGE); 
    attachInterrupt(ENCODER_DT,  encoderChange, CHANGE);
}

void IRAM_ATTR encoderChange()
{
    portENTER_CRITICAL_ISR(&(mux));

    old_AB <<= 2;
	int8_t ENC_PORT = ((digitalRead(ENCODER_CLK)) ? (1 << 1) : 0) | ((digitalRead(ENCODER_DT)) ? (1 << 0) : 0);
    old_AB |= ( ENC_PORT & 0x03 );
    encoder0Pos += ( enc_states[( old_AB & 0x0f )]);	

    if (encoder0Pos > (_maxEncoderValue))
        encoder0Pos = _circleValues ? _minEncoderValue : _maxEncoderValue;
    if (encoder0Pos < (_minEncoderValue))
        encoder0Pos = _circleValues ? _maxEncoderValue : _minEncoderValue;		

    encoderValue = encoder0Pos;

    portEXIT_CRITICAL_ISR(&(mux));
}
