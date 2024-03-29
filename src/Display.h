#pragma once 

#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <MD_MAXPanel.h>
#include <SPI.h>
#include <stdint.h>
#include <inttypes.h>
#include "Configuration.h"
#include "Latin1.h"
#include "Menu.h"
#include "Encoder.h"
#include "clock/Clock.h"
#include "sys_fixed_single.h"
#include "gameoflife/Gameoflife.h"
#include "DHTesp.h"

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
    Clock clo;
    DHTesp dht;
    TempAndHumidity sensorData;
    int textCount = 0;
    int curText = 0;
    uint32_t goltimeLastRun = 0;
    uint8_t golsameCount = 10;
    uint32_t gollastCount = 0;
    uint8_t oldstate;
   	uint8_t stateInt = 0;
    uint32_t statetimeLastRun = 0;
    uint32_t menuTimeout = 0;

    typedef struct 
    {
        String text;
        textPosition_t align;
        int speed;
        int pause;
        textEffect_t effectIn;
        textEffect_t effectOut;        
    }texteAusgabe; 

protected:
public:
    static Display& instance()
    {
       static Display _instance;
       return _instance;
    }
    ~Display() {}
    MD_Parola *parola;
    MD_MAXPanel *maxPan;
    void init(int encoderSwitchPin, Encoder enc, Clock clo);
    void displayText(String text, textPosition_t align, uint16_t speed, uint16_t pause, textEffect_t effectIn, textEffect_t effectOut);
    void displayTexte(String text[], textPosition_t align, uint16_t speed, uint16_t pause, textEffect_t effectIn, textEffect_t effectOut);
    void displayTexte(texteAusgabe ausgabe[]);
    void setDisplayState();
    void render();
    void animateUntilButtonPress(bool repeat = false);
    uint8_t intensity = 0;

    String scrollText = ""; 
    texteAusgabe clockausgabe;
    bool autostate;
    uint8_t automatikArray[20];
    uint8_t autozeitArray[20];
    uint8_t autozaehler = 1;
    uint8_t animationStart = 4; 
    uint8_t animationEnde = 4; 
    uint8_t spriteStart = 4; 
    uint8_t spriteEnde = 4; 
    uint16_t pause = 2000;
    String wlanPassword = "";
    String wlanssid = "";

    uint8_t xDisplays = MAX7219_X_DISPLAYS;
    uint8_t yDisplays = MAX7219_Y_DISPLAYS;

    String sensorString;
    String clockText;
};
