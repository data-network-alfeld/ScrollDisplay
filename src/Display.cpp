#include "Display.h"

Display::Display() {
}


void Display::init(int encoderSwitchPin, Encoder enc)
{
	this->enc = enc; 
    parola.begin();  // Start Parola
}

void Display::displayText(String text, textPosition_t align, uint16_t speed, uint16_t pause, textEffect_t effectIn, textEffect_t effectOut)
{
	Latin1::utf8tolatin1(text).toCharArray(textBuffer, sizeof(textBuffer));
	parola.displayText(textBuffer, align, speed, pause, effectIn, effectOut);
}

void Display::setDisplayState()
{
	switch (state)
	{
		case SCROLLTEXT:
			break;
		case TEMPERATURE: 
			break; 
		case MENU: 
			displayText(menuitemStrings[menuitem] , PA_LEFT, 0, 0, PA_PRINT);
			break; 
		default:
			break;
	}
}

void Display::render() 
{
	// Wurde am Encoder gedreht? 
	if (enc.getEncoderChanged())
	{
		Serial.println(enc.getCount());

		menuitem = enc.getCount();
		setDisplayState();
	}
	
	// Wurde der Taster gedrückt? 
	if (Encoder::buttonPressed)
	{
		Encoder::buttonPressed = 0;

		Serial.println(menuitemStrings[menuitem]);
	}

	if (parola.displayAnimate()) // If finished displaying message
	{
		parola.displayReset();  // Reset and display it again
	}
}
