#include "Display.h"
#include "Sprite.h"
#include "randomseed.h"

Display::Display() {
}

void Display::init(int encoderSwitchPin, Encoder enc, Clock clo)
{
	this->clo = clo;
	this->enc = enc; 
    parola.begin();  // Start Parola
	parola.setIntensity(intensity);
	maxPan.begin();
	maxPan.setIntensity(intensity);
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
	Latin1::utf8tolatin1(ausgabe[curText].text).toCharArray(textBuffer, sizeof(textBuffer));
	parola.displayText(textBuffer, ausgabe[curText].align, ausgabe[curText].speed, ausgabe[curText].pause, ausgabe[curText].effectIn, ausgabe[curText].effectOut);
	if (ausgabe[curText].effectIn == (textEffect_t) PA_SPRITE || ausgabe[curText].effectOut == (textEffect_t) PA_SPRITE)
	{
		parola.setSpriteData(sprite[spriteStart].data, sprite[spriteStart].width, sprite[spriteStart].frames, sprite[spriteEnde].data, sprite[spriteEnde].width, sprite[spriteEnde].frames);
	}
}

void Display::setDisplayState()
{
	if (oldstate != state) {oldstate = state;curText=0;}
	parola.setFont(NULL);
	switch (state)
	{
		case SCROLLTEXT:
			displayText(scrollText , PA_CENTER, enc.getCount() * 10, pause, (textEffect_t) animationStart,(textEffect_t) animationEnde);
			break;
		case TEMPERATURE: 
			break; 
		case CLOCK: 
		{
			parola.setFont(_sys_fixed_single);
			String clockText[] = 
			{
				clo.getTime(),
			};
			textCount = sizeof(clockText) / sizeof(String);
			displayTexte(clockText, PA_CENTER, enc.getCount() * 10, pause, PA_PRINT ,PA_NO_EFFECT);
			break;	
		}
		case CLOCKANDDATE: 
		{
			parola.setFont(_sys_fixed_single);
			texteAusgabe clockausgabe[] = 
			{
				{ clo.getTime(),PA_CENTER, enc.getCount()*10,pause,PA_PRINT, PA_NO_EFFECT },
				{ clo.getTime(),PA_CENTER, enc.getCount()*10,pause,PA_PRINT, PA_NO_EFFECT },
				{ clo.getTime(),PA_CENTER, enc.getCount()*10,pause,PA_PRINT, PA_NO_EFFECT },
				{ clo.getTime(),PA_CENTER, enc.getCount()*10,pause,PA_PRINT, PA_NO_EFFECT },
				{ clo.getTime(),PA_CENTER, enc.getCount()*10,pause,PA_PRINT, PA_NO_EFFECT },
				{ clo.getTime(),PA_CENTER, enc.getCount()*10,pause,PA_PRINT, PA_NO_EFFECT },
				{ clo.getTime(),PA_CENTER, enc.getCount()*10,pause,PA_PRINT, PA_NO_EFFECT },
				{ clo.getTime(),PA_CENTER, enc.getCount()*10,pause,PA_PRINT, PA_NO_EFFECT },
				{ clo.getWeekday(),PA_CENTER, enc.getCount()*10,pause,PA_SPRITE, PA_SPRITE },
//				{ "Monat",PA_CENTER, enc.getCount()*10,pause,PA_SCROLL_UP_LEFT, PA_SCROLL_DOWN_RIGHT },
//				{ clo.getMonth(),PA_CENTER, enc.getCount()*10,pause,PA_MESH, PA_CLOSING_CURSOR },
				{ clo.getDate(),PA_CENTER, enc.getCount()*10,pause,PA_SCROLL_UP_LEFT, PA_GROW_DOWN },
			};
			textCount = sizeof(clockausgabe) / sizeof(clockausgabe[0]);
			displayTexte(clockausgabe);

			break; 
		}
		case GAMEOFLIFE:
			maxPan.clear();
			break;
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
				maxPan.clear();
				menuitem = enc.getCount();
				setDisplayState();
				break;
			case STATE::SCROLLTEXT:
				maxPan.clear();
				parola.displayClear();
				setDisplayState();
				break; 
			case STATE::CLOCK:
				maxPan.clear();
				parola.displayClear();
				setDisplayState();
				break; 
			case STATE::CLOCKANDDATE:
				maxPan.clear();
				parola.displayClear();
				setDisplayState();
				break; 
			case STATE::GAMEOFLIFE:
				maxPan.clear();
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
			case GAMEOFLIFE:
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
			if (textCount != 0) 
			{
				curText = (curText+ 1) % textCount;
			}
			setDisplayState();
			//parola.displayReset();  // Reset and display it again
		}
		if (state == STATE::CLOCKANDDATE)
		{
			if (textCount != 0) 
			{
				curText = (curText+ 1) % textCount;
			}
			setDisplayState();
			//parola.displayReset();  // Reset and display it again
		}
		if (state == STATE::GAMEOFLIFE)
		{
			Gameoflife gol;

			uint32_t count = gol.countCells();
			
			if (gollastCount == count) golsameCount++; else golsameCount = 0;

			if (golsameCount >= 4)
			{
				maxPan.clear();     // mark the end of the display ...
				delay(1000);    // ... with a minor pause!
				gol.firstGeneration();
				golsameCount = 0;
			}
			gollastCount = count;
				
			// Check if next generation time
			if (millis() - goltimeLastRun >= 150)
			{
				goltimeLastRun = millis();
				gol.nextGeneration();
			}
			//parola.displayReset();  // Reset and display it again
		}
	}

	if (autostate) {
		if (millis() - statetimeLastRun >= 30000)
		{
			statetimeLastRun = millis();
			Serial.print("Alter State = ");
			Serial.println(state);

 			if (state == STATE::SCROLLTEXT) {
				state = STATE::CLOCK;
				setDisplayState();		
			} 
 			else if (state == STATE::CLOCK)
			{
				state = STATE::GAMEOFLIFE;
				setDisplayState();		
			}
			else if (state == STATE::CLOCKANDDATE)
			{
				state = STATE::SCROLLTEXT;
				setDisplayState();		
			}
			else if (state == STATE::GAMEOFLIFE)
			{
				state = STATE::CLOCKANDDATE;
				setDisplayState();		
			}
			Serial.print("neuer State = ");
			Serial.println(state);
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