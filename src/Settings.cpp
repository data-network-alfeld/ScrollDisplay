#include "Settings.h"

Preferences prefs;

void beginConfiguration()
{
    prefs.begin("scroll", false);
}

void readConfiguration()
{
    Display& disp = Display::instance();

    disp.scrollText = prefs.getString("text", "Ferienpass 19"); 
    disp.animationStart = prefs.getUChar("animationStart", 4);
    disp.animationEnde = prefs.getUChar("animationEnde", 4);
    disp.spriteStart = prefs.getUChar("spriteStart", 4);
    disp.spriteEnde = prefs.getUChar("spriteEnde", 4);
    disp.pause = prefs.getUShort("pause", 2000);

    disp.intensity = prefs.getUChar("intensity", 0);
    disp.parola.setIntensity(disp.intensity);
}

void saveConfiguration()
{
    Display& disp = Display::instance();
    prefs.putString("text", disp.scrollText);
    prefs.putUChar("animationStart", disp.animationStart);
    prefs.putUChar("animationEnde", disp.animationEnde);
    prefs.putUChar("spriteStart", disp.spriteStart);
    prefs.putUChar("spriteEnde", disp.spriteEnde);
    prefs.putUShort("pause", disp.pause);
    prefs.putUChar("intensity", disp.intensity);
}