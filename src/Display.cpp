#include "Display.h"
#include "Sprite.h"
#include "randomseed.h"

Gameoflife gol;

			static uint32_t timeLastRun = 0;
			static uint8_t sameCount = 10;
			static uint32_t lastCount = 0;




Display::Display() {
}

void Display::init(int encoderSwitchPin, Encoder enc, Clock clo)
{
	this->clo = clo;
	this->enc = enc; 
    parola.begin();  // Start Parola
	parola.setIntensity(intensity);
	max72xx.begin();

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

			// setup sachen first gen nur einmal
			max72xx.clear();
//			gol.init();

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
				max72xx.clear();
				menuitem = enc.getCount();
				setDisplayState();
				break;
			case STATE::SCROLLTEXT:
				max72xx.clear();
				parola.displayClear();
				setDisplayState();
				break; 
			case STATE::CLOCK:
				max72xx.clear();
				parola.displayClear();
				setDisplayState();
				break; 
			case STATE::CLOCKANDDATE:
				max72xx.clear();
				parola.displayClear();
				setDisplayState();
				break; 
			case STATE::GAMEOFLIFE:
				max72xx.clear();
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
				curText = (++curText) % textCount;
			}
			setDisplayState();
			//parola.displayReset();  // Reset and display it again
		}
		if (state == STATE::CLOCKANDDATE)
		{
			if (textCount != 0) 
			{
				curText = (++curText) % textCount;
			}
			setDisplayState();
			//parola.displayReset();  // Reset and display it again
		}
		if (state == STATE::GAMEOFLIFE)
		{
			// die sachen vom loop hierrein

/*			static uint32_t timeLastRun = 0;
			static uint8_t sameCount = 10;
			static uint32_t lastCount = 0;
			*/
			uint32_t count = gol.countCells();
			
			if (lastCount == count) sameCount++; else sameCount = 0;

			if (sameCount >= 4)
			{
				max72xx.clear();     // mark the end of the display ...
				delay(1000);    // ... with a minor pause!
				Serial.println("hier bin ich");
				gol.firstGeneration();
				sameCount = 0;
			}
			lastCount = count;
				
			// Check if next generation time
			if (millis() - timeLastRun >= 150)
			{
				timeLastRun = millis();
				gol.nextGeneration();
			}

		//	setDisplayState();
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