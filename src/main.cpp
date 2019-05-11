#include <Arduino.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#include "configuration.h"
#include "encoder.h"
#include "menu.h"

encoder enc; 
MD_Parola P = MD_Parola(MD_MAX72XX::FC16_HW, MAX7219_CS, 8);
char textBuffer[] = "Data Network Alfeld e.V.";
textEffect_t scrollEffect = PA_SCROLL_LEFT;
textPosition_t scrollAlign = PA_LEFT;  // how to aligh the text
int scrollPause = 0; // ms of pause after finished displaying message
int scrollSpeed = 50;

void setDisplayState(); 

void setup()
{
	Serial.begin(115200);
	
	// Drehencoder initialisieren
	enc.attachSingleEdge(ENCODER_DT, ENCODER_CLK);

	P.begin();  // Start Parola

	// configure Parola
	//P.displayText(textBuffer, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
	setDisplayState();
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
			P.displayText((char*) menuitemStrings[menuitem] , PA_LEFT, 0, 0, PA_PRINT);
			break; 
		default:
			break;
	}
	
}

void loop()
{
	Serial.println(enc.getCount());

	if (P.displayAnimate()) // If finished displaying message
	{
		//P.displayReset();  // Reset and display it again
	}
}
