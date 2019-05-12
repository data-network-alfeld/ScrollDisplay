#include <Arduino.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#include "configuration.h"
#include "encoder.h"
#include "menu.h"
#include "CP437.h"

encoder enc; 
MD_Parola P = MD_Parola(MD_MAX72XX::FC16_HW, MAX7219_CS, 8);
char textBuffer[128];
textEffect_t scrollEffect = PA_SCROLL_LEFT;
textPosition_t scrollAlign = PA_LEFT;  // how to aligh the text
int scrollPause = 0; // ms of pause after finished displaying message
int scrollSpeed = 50;

void setDisplayState(); 



uint8_t iflag = 0;
void keyPressed()
{
	iflag = !iflag; 
	if (iflag)
	{
		Serial.println("-5 +5");
		enc.setLimits(-5, 5);
	}
	else
	{
		Serial.println("-10 +10");
		enc.setLimits(-10, 10);
	}
}


void setup()
{
	Serial.begin(115200);
	
	// Drehencoder initialisieren
	enc.attachSingleEdge(ENCODER_DT, ENCODER_CLK);
	enc.attachButton(ENCODER_SW);

	P.begin();  // Start Parola

	// configure Parola
	//P.displayText(textBuffer, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
	setDisplayState();

	enc.setLimits(0, _MENUITEMS_LENGTH - 1);

}

void displayText(String text, textPosition_t align, uint16_t speed, uint16_t pause, textEffect_t effectIn, textEffect_t effectOut = PA_NO_EFFECT)
{
	CP437::utf8tocp437(text).toCharArray(textBuffer, sizeof(textBuffer));
	P.displayText(textBuffer, align, speed, pause, effectIn, effectOut);
}

void setDisplayState()
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

void loop()
{
	if (enc.getEncoderChanged())
	{
		Serial.println(enc.getCount());


		menuitem = enc.getCount();
		setDisplayState();
	}
 
	if (P.displayAnimate()) // If finished displaying message
	{
		//P.displayReset();  // Reset and display it again
	}
}

