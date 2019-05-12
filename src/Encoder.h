#pragma once
#include <Arduino.h>
#include <driver/gpio.h>
extern "C" {
  #include "soc/pcnt_struct.h"
}

#include "driver/pcnt.h"
#define MAX_ESP32_ENCODERS PCNT_UNIT_MAX
#define DEBOUNCE_PERIOD 200

class Encoder {
private:
	void attach(int aPintNumber, int bPinNumber, boolean fullQuad);
	boolean attached=false;

	static  pcnt_isr_handle_t user_isr_handle; //user's ISR service handle
    bool direction;
    bool working;
    int16_t lastHWcount = 0;
    uint8_t encoderChanged = 0;
    int16_t min = -30000;
    int16_t max = 30000;

public:
	Encoder();
	~Encoder();
	void attachHalfQuad(int aPintNumber, int bPinNumber);
	void attachSingleEdge(int aPintNumber, int bPinNumber);
	void attachButton(int buttonPin);
	//void attachHalfQuad(int aPintNumber, int bPinNumber);
	int32_t getCount();
	int32_t getCountRaw();
  uint8_t getEncoderChanged();
  void setLimits(int16_t min, int16_t max);
	
	boolean isAttached(){return attached;}
	void setCount(int32_t value);
	static Encoder *encoders[MAX_ESP32_ENCODERS];
	static bool attachedInterrupt;
	gpio_num_t aPinNumber;
	gpio_num_t bPinNumber;
	pcnt_unit_t unit;
	bool fullQuad=false;
	int countsMode = 2;
	volatile int32_t count=0;
	pcnt_config_t r_enc_config;
	static volatile uint32_t debounceTimeout; 
	static volatile uint8_t buttonPressed;
};
