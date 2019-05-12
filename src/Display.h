#pragma once 

#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <stdint.h>
#include <inttypes.h>
#include "Configuration.h"
#include "Latin1.h"
#include "Menu.h"
#include "Encoder.h"

class Display
{
private:
    Display();
   
    char textBuffer[128];
    textEffect_t scrollEffect = PA_SCROLL_LEFT;
    textPosition_t scrollAlign = PA_LEFT;  // how to aligh the text
    int scrollPause = 0; // ms of pause after finished displaying message
    int scrollSpeed = 50;
    Encoder enc;
protected:
public:
    static Display& instance()
    {
       static Display _instance;
       return _instance;
    }
    ~Display() {}
    MD_Parola parola = MD_Parola(MD_MAX72XX::FC16_HW, MAX7219_CS, 8);
    void init(int encoderSwitchPin, Encoder enc);
    void displayText(String text, textPosition_t align, uint16_t speed, uint16_t pause, textEffect_t effectIn, textEffect_t effectOut = PA_NO_EFFECT);
    void setDisplayState();
    void render();
    void animateUntilButtonPress(bool repeat = false);
    uint8_t intensity = 15;
};
