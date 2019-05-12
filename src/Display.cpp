#include "Display.h"

Display::Display() {
}

void Display::init(int encoderSwitchPin, Encoder enc)
{
	this->enc = enc; 
    parola.begin();  // Start Parola
	parola.setIntensity(intensity);
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
			displayText("Woohoo \\o/" , PA_CENTER, enc.getCount() * 10, 2000, textEffect_t::PA_SCROLL_LEFT);
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
		switch (state)
		{
			case STATE::MENU:
				menuitem = enc.getCount();
				setDisplayState();
				break;
			case STATE::SCROLLTEXT:
				parola.displayClear();
				setDisplayState();
				break; 
			default:
				break;
		}
	}
	
	// Wurde der Taster gedrückt? 
	if (Encoder::buttonPressed)
	{
		Encoder::buttonPressed = 0;

		switch (state)
		{
			case SCROLLTEXT:
				enc.setLimits(0, _MENUITEMS_LENGTH - 1);
				state = STATE::MENU;
				setDisplayState();
				break;
			case MENU:
				menuItemPressed(enc);
				break;
			default:
				break;
		}
	}

	if (parola.displayAnimate()) // If finished displaying message
	{
		if (state == STATE::SCROLLTEXT)
		{
			setDisplayState();
			//parola.displayReset();  // Reset and display it again
		}
	}
}
