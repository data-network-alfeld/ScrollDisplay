#pragma once 

#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <stdint.h>
#include <inttypes.h>
#include "configuration.h"
#include "Latin1.h"
#include "menu.h"

class Display
{
private:
    MD_Parola parola = MD_Parola(MD_MAX72XX::FC16_HW, MAX7219_CS, 8);;
    char textBuffer[128];
    textEffect_t scrollEffect = PA_SCROLL_LEFT;
    textPosition_t scrollAlign = PA_LEFT;  // how to aligh the text
    int scrollPause = 0; // ms of pause after finished displaying message
    int scrollSpeed = 50;
protected:
public:
    Display();
    void init(int encoderSwitchPin);
    void displayText(String text, textPosition_t align, uint16_t speed, uint16_t pause, textEffect_t effectIn, textEffect_t effectOut = PA_NO_EFFECT);
    void setDisplayState();
    void render();
};
