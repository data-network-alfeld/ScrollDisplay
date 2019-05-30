#include "Display.h"
#include "Sprite.h"

Display::Display() {
}

void Display::init(int encoderSwitchPin, Encoder enc, Clock clo)
{
	this->clo = clo;
	this->enc = enc; 
    parola.begin();  // Start Parola
	parola.setIntensity(intensity);
}

void Display::displayText(String text, textPosition_t align, uint16_t speed, uint16_t pause, textEffect_t effectIn, textEffect_t effectOut)
{
	Latin1::utf8tolatin1(text).toCharArray(textBuffer, sizeof(textBuffer));
	parola.displayText(textBuffer, align, speed, pause, effectIn, effectOut);
	if (effectIn == (textEffect_t) PA_SPRITE || effectOut == (textEffect_t) PA_SPRITE)
	{
		parola.setSpriteData(sprite[spriteStart].data, sprite[spriteStart].width, sprite[spriteStart].frames, sprite[spriteEnde].data, sprite[spriteEnde].width, sprite[spriteEnde].frames);
	}
}

void Display::displayTexte(String text[], textPosition_t align, uint16_t speed, uint16_t pause, textEffect_t effectIn, textEffect_t effectOut)
{
	Latin1::utf8tolatin1(text[curText]).toCharArray(textBuffer, sizeof(textBuffer));
	parola.displayText(textBuffer, align, speed, pause, effectIn, effectOut);
	if (effectIn == (textEffect_t) PA_SPRITE || effectOut == (textEffect_t) PA_SPRITE)
	{
		parola.setSpriteData(sprite[spriteStart].data, sprite[spriteStart].width, sprite[spriteStart].frames, sprite[spriteEnde].data, sprite[spriteEnde].width, sprite[spriteEnde].frames);
	}
}

void Display::displayTexte(texteAusgabe ausgabe[])
{
	Serial.println(ausgabe[curText].text);
	Latin1::utf8tolatin1(ausgabe[curText].text).toCharArray(textBuffer, sizeof(textBuffer));
	parola.displayText(textBuffer, ausgabe[curText].align, ausgabe[curText].speed, ausgabe[curText].pause, ausgabe[curText].effectIn, ausgabe[curText].effectOut);
	if (ausgabe[curText].effectIn == (textEffect_t) PA_SPRITE || ausgabe[curText].effectOut == (textEffect_t) PA_SPRITE)
	{
		parola.setSpriteData(sprite[spriteStart].data, sprite[spriteStart].width, sprite[spriteStart].frames, sprite[spriteEnde].data, sprite[spriteEnde].width, sprite[spriteEnde].frames);
	}
}

void Display::setDisplayState()
{
	switch (state)
	{
		case SCROLLTEXT:
			displayText(scrollText , PA_CENTER, enc.getCount() * 10, pause, (textEffect_t) animationStart,(textEffect_t) animationEnde);
			break;
		case TEMPERATURE: 
			break; 
		case CLOCK: 
		{

			String clockText[] = 
			{
				clo.getTime(),
			};
			textCount = sizeof(clockText) / sizeof(String);
			displayTexte(clockText, PA_LEFT, enc.getCount() * 10, pause, PA_PRINT ,PA_NO_EFFECT);
		
			break;	
		}
		case CLOCKANDDATE: 
		{
			texteAusgabe test3[] = 
			{
				{ clo.getTime(),PA_CENTER, enc.getCount()*10,pause,PA_PRINT, PA_NO_EFFECT },
				{ clo.getTime(),PA_CENTER, enc.getCount()*10,pause,PA_PRINT, PA_NO_EFFECT },
				{ clo.getTime(),PA_CENTER, enc.getCount()*10,pause,PA_PRINT, PA_NO_EFFECT },
				{ clo.getTime(),PA_CENTER, enc.getCount()*10,pause,PA_PRINT, PA_NO_EFFECT },
				{ clo.getTime(),PA_CENTER, enc.getCount()*10,pause,PA_PRINT, PA_NO_EFFECT },
				{ clo.getTime(),PA_CENTER, enc.getCount()*10,pause,PA_PRINT, PA_NO_EFFECT },
				{ clo.getTime(),PA_CENTER, enc.getCount()*10,pause,PA_PRINT, PA_NO_EFFECT },
				{ clo.getTime(),PA_CENTER, enc.getCount()*10,pause,PA_PRINT, PA_NO_EFFECT },
				{ clo.getWeekday(),PA_CENTER, enc.getCount()*10,pause,PA_SCROLL_DOWN, PA_SCROLL_UP },
//				{ "Monat",PA_CENTER, enc.getCount()*10,pause,PA_SCROLL_UP_LEFT, PA_SCROLL_DOWN_RIGHT },
//				{ clo.getMonth(),PA_CENTER, enc.getCount()*10,pause,PA_MESH, PA_CLOSING_CURSOR },
				{ clo.getDate(),PA_CENTER, enc.getCount()*10,pause,PA_SCROLL_UP_LEFT, PA_GROW_DOWN },
			};
			textCount = sizeof(test3) / sizeof(test3[0]);
			displayTexte(test3);

			break; 
		}
		case MENU: 
			displayText(menuitemStrings[menuitem] , PA_LEFT, 0, 0, PA_PRINT,PA_NO_EFFECT);
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
			case STATE::CLOCK:
				parola.displayClear();
				setDisplayState();
				break; 
			case STATE::CLOCKANDDATE:
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
			case CLOCK:
				enc.setLimits(0, _MENUITEMS_LENGTH - 1);
				state = STATE::MENU;
				setDisplayState();
				break;
			case CLOCKANDDATE:
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
		if (state == STATE::CLOCK)
		{
			curText = (++curText) % textCount;
			setDisplayState();
			//parola.displayReset();  // Reset and display it again
		}
		if (state == STATE::CLOCKANDDATE)
		{
			curText = (++curText) % textCount;
			setDisplayState();
			//parola.displayReset();  // Reset and display it again
		}
	}
}

void Display::animateUntilButtonPress(bool repeat)
{
	while (!parola.displayAnimate()) 
	{
		delay(10);

		if (Encoder::buttonPressed) 
		{
			Encoder::buttonPressed = 0;
			parola.displayClear();
			return;
		}

		if (repeat)
		{
			if (parola.displayAnimate())
				parola.displayReset();
		}
		
		wm.process();
	}
}