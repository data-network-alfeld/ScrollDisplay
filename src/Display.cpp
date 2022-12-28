#include "Display.h"
#include "Sprite.h"
#include "randomseed.h"

Display::Display() {
}

void Display::init(int encoderSwitchPin, Encoder enc, Clock clo)
{
	this->clo = clo;
	this->enc = enc; 

    parola = new MD_Parola(MD_MAX72XX::FC16_HW, MAX7219_CS, xDisplays * yDisplays);
    parola->begin();  // Start Parola
	parola->setIntensity(intensity);
	
	maxPan = new MD_MAXPanel(parola->getGraphicObject(), xDisplays, yDisplays);
	maxPan->begin();
	maxPan->setIntensity(intensity);
	dht.setup(DHT_PIN,DHTesp::AUTO_DETECT);
}

void Display::displayText(String text, textPosition_t align, uint16_t speed, uint16_t pause, textEffect_t effectIn, textEffect_t effectOut)
{
	Serial.println(text);
	Latin1::utf8tolatin1(text).toCharArray(textBuffer, sizeof(textBuffer));
	parola->displayText(textBuffer, align, speed, pause, effectIn, effectOut);
	if (effectIn == (textEffect_t) PA_SPRITE || effectOut == (textEffect_t) PA_SPRITE)
	{
		parola->setSpriteData(sprite[spriteStart].data, sprite[spriteStart].width, sprite[spriteStart].frames, sprite[spriteEnde].data, sprite[spriteEnde].width, sprite[spriteEnde].frames);
	}
}

void Display::displayTexte(String text[], textPosition_t align, uint16_t speed, uint16_t pause, textEffect_t effectIn, textEffect_t effectOut)
{
	Latin1::utf8tolatin1(text[curText]).toCharArray(textBuffer, sizeof(textBuffer));
	parola->displayText(textBuffer, align, speed, pause, effectIn, effectOut);
	if (effectIn == (textEffect_t) PA_SPRITE || effectOut == (textEffect_t) PA_SPRITE)
	{
		parola->setSpriteData(sprite[spriteStart].data, sprite[spriteStart].width, sprite[spriteStart].frames, sprite[spriteEnde].data, sprite[spriteEnde].width, sprite[spriteEnde].frames);
	}
}

void Display::displayTexte(texteAusgabe ausgabe[])
{
	Latin1::utf8tolatin1(ausgabe[curText].text).toCharArray(textBuffer, sizeof(textBuffer));
	parola->displayText(textBuffer, ausgabe[curText].align, ausgabe[curText].speed, ausgabe[curText].pause, ausgabe[curText].effectIn, ausgabe[curText].effectOut);
	if (ausgabe[curText].effectIn == (textEffect_t) PA_SPRITE || ausgabe[curText].effectOut == (textEffect_t) PA_SPRITE)
	{
		parola->setSpriteData(sprite[spriteStart].data, sprite[spriteStart].width, sprite[spriteStart].frames, sprite[spriteEnde].data, sprite[spriteEnde].width, sprite[spriteEnde].frames);
	}
}

void Display::setDisplayState()
{
	if (oldstate != state) {oldstate = state;curText=0;}
	parola->setFont(NULL);

	switch (state)
	{
		case SCROLLTEXT:
			displayText(scrollText , PA_CENTER, enc.getCount() * 10, pause, (textEffect_t) animationStart,(textEffect_t) animationEnde);
			break;
		case TEMPERATURE: 
		{		
			sensorData = dht.getTempAndHumidity();
			if (dht.getStatus() != 0) 
			{
				displayText("Keine Werte" , PA_CENTER, enc.getCount() * 10, pause, PA_PRINT ,PA_NO_EFFECT);
				Serial.println(dht.getStatusString());
			}
			 else 
			{
				String sensorString = String( int (sensorData.temperature)) + String("°C   ") +  String( int (sensorData.humidity)) + String("%");
				textCount = 1;
				displayTexte(&sensorString , PA_CENTER, enc.getCount() * 10, 2000, (textEffect_t) animationStart,(textEffect_t) animationEnde);
//				Serial.printf("Temperatur %.0f , Feuchtigkeit %.0f\n", sensorData.temperature, sensorData.humidity);
			}
			break; 
		}
		case CLOCK: 
		{
			parola->setFont(_sys_fixed_single);
			String clockText = String(clo.getTime());
			textCount = 1;
			displayTexte(&clockText, PA_CENTER, enc.getCount() * 10, 200, PA_PRINT ,PA_NO_EFFECT);
			break;	
		}
		case CLOCKANDDATE: 
		{
			parola->setFont(_sys_fixed_single);
			texteAusgabe clockausgabe[] = 
			{
				{ clo.getTime(),PA_CENTER, enc.getCount()*10, 1000,PA_PRINT, PA_NO_EFFECT },
				{ clo.getTime(),PA_CENTER, enc.getCount()*10, 1000,PA_PRINT, PA_NO_EFFECT },
				{ clo.getTime(),PA_CENTER, enc.getCount()*10, 1000,PA_PRINT, PA_NO_EFFECT },
				{ clo.getTime(),PA_CENTER, enc.getCount()*10, 1000,PA_PRINT, PA_NO_EFFECT },
				{ clo.getTime(),PA_CENTER, enc.getCount()*10, 1000,PA_PRINT, PA_NO_EFFECT },
				{ clo.getTime(),PA_CENTER, enc.getCount()*10, 1000,PA_PRINT, PA_NO_EFFECT },
				{ clo.getTime(),PA_CENTER, enc.getCount()*10, 1000,PA_PRINT, PA_NO_EFFECT },
				{ clo.getTime(),PA_CENTER, enc.getCount()*10, 1000,PA_PRINT, PA_NO_EFFECT },
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
			maxPan->clear();
			break;
		case WEEKDAY:
			displayText(clo.getWeekday() , PA_CENTER, enc.getCount() * 10, pause, (textEffect_t) animationStart,(textEffect_t) animationEnde);
			break;
		case DATE:
			displayText(clo.getDate() , PA_CENTER, enc.getCount() * 10, pause, (textEffect_t) animationStart,(textEffect_t) animationEnde);
			break;
		case MONTH:
			displayText(clo.getMonth() , PA_CENTER, enc.getCount() * 10, pause, (textEffect_t) animationStart,(textEffect_t) animationEnde);
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
				maxPan->clear();
				menuitem = enc.getCount();
				setDisplayState();
				break;
			case STATE::SCROLLTEXT:
				maxPan->clear();
				parola->displayClear();
				setDisplayState();
				break; 
			case STATE::TEMPERATURE:
				maxPan->clear();
				parola->displayClear();
				setDisplayState();
				break; 
			case STATE::CLOCK:
				maxPan->clear();
				parola->displayClear();
				setDisplayState();
				break; 
			case STATE::CLOCKANDDATE:
				maxPan->clear();
				parola->displayClear();
				setDisplayState();
				break; 
			case STATE::GAMEOFLIFE:
				maxPan->clear();
				parola->displayClear();
				setDisplayState();
				break; 
			case STATE::WEEKDAY:
				maxPan->clear();
				parola->displayClear();
				setDisplayState();
				break; 
			case STATE::DATE:
				maxPan->clear();
				parola->displayClear();
				setDisplayState();
				break; 
			case STATE::MONTH:
				maxPan->clear();
				parola->displayClear();
				setDisplayState();
				break; 
			default:
				break;
		}		
	}
	
	// Check for timeout in menu (avoid spurious button presses)
	if (state == STATE::MENU)
	{
		if (millis() >= menuTimeout + (180 * 1000))
		{
			menuTimeout = millis();
			//Serial.println("menu autoclose");
			Encoder::buttonPressed = 1;
		}
	}

	// Wurde der Taster gedrückt? 
	if (Encoder::buttonPressed)
	{
		Encoder::buttonPressed = 0;

		switch (state)
		{
			case SCROLLTEXT:
			case TEMPERATURE:
			case CLOCK:
			case CLOCKANDDATE:
			case GAMEOFLIFE:
			case WEEKDAY:
			case DATE:
			case MONTH:
				enc.setLimits(0, _MENUITEMS_LENGTH - 1);
				state = STATE::MENU;
				setDisplayState();
				menuTimeout = millis();
				break;
			case MENU:
				menuItemPressed(enc);
				break;
			default:
				break;
		}
	}

	if (parola->displayAnimate()) // If finished displaying message
	{
		if (state == STATE::SCROLLTEXT)
		{
			setDisplayState();
			//parola->displayReset();  // Reset and display it again
		}
		if (state == STATE::TEMPERATURE)
		{
			if (textCount != 0) 
			{
				curText = (curText+ 1) % textCount;
			}
			setDisplayState();
			//parola->displayReset();  // Reset and display it again
		}
		if (state == STATE::CLOCK)
		{
			if (textCount != 0) 
			{
				curText = (curText+ 1) % textCount;
			}
			setDisplayState();
			//parola->displayReset();  // Reset and display it again
		}
		if (state == STATE::CLOCKANDDATE)
		{
			if (textCount != 0) 
			{
				curText = (curText+ 1) % textCount;
			}
			setDisplayState();
			//parola->displayReset();  // Reset and display it again
		}
		if (state == STATE::GAMEOFLIFE)
		{
			Gameoflife gol;

			uint32_t count = gol.countCells();
			
			if (gollastCount == count) golsameCount++; else golsameCount = 0;

			if (golsameCount >= 4)
			{
				maxPan->clear();     // mark the end of the display ...
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
			//parola->displayReset();  // Reset and display it again
		}
		if (state == STATE::WEEKDAY)
		{
			if (textCount != 0) 
			{
				curText = (curText+ 1) % textCount;
			}
			setDisplayState();
			//parola->displayReset();  // Reset and display it again
		}
		if (state == STATE::DATE)
		{
			if (textCount != 0) 
			{
				curText = (curText+ 1) % textCount;
			}
			setDisplayState();
			//parola->displayReset();  // Reset and display it again
		}
		if (state == STATE::MONTH)
		{
			if (textCount != 0) 
			{
				curText = (curText+ 1) % textCount;
			}
			setDisplayState();
			//parola->displayReset();  // Reset and display it again
		}

	}

	if (autostate && state != STATE::MENU) {
		if (millis() - statetimeLastRun >= (autozeitArray[stateInt] * 1000))
		{
			statetimeLastRun = millis();
			stateInt++;

			if (stateInt > autozaehler) {
				stateInt = 1;
			}
			state = automatikArray[stateInt];
			setDisplayState();
		}
	}
}

void Display::animateUntilButtonPress(bool repeat)
{
	while (!parola->displayAnimate()) 
	{
		delay(10);

		if (Encoder::buttonPressed) 
		{
			Encoder::buttonPressed = 0;
			parola->displayClear();
			return;
		}

		if (repeat)
		{
			if (parola->displayAnimate())
				parola->displayReset();
		}
		
		wm.process();
	}
}