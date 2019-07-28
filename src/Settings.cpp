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
    firmwareauswahl = prefs.getUShort("firmwareauswahl",0);
    disp.intensity = prefs.getUShort("intensity", 0);

    state = prefs.getUShort("state", STATE::SCROLLTEXT);
    disp.autostate = prefs.getBool("autostate", false);
    disp.wlanPassword = prefs.getString("wlanpassword", "");
    disp.wlanssid = prefs.getString("wlanssid", "");
    disp.xDisplays = prefs.getUChar("xdisplays", MAX7219_X_DISPLAYS);
    disp.yDisplays = prefs.getUChar("ydisplays", MAX7219_Y_DISPLAYS);
    disp.autozaehler = prefs.getUShort("autozaehler", disp.autozaehler);
    prefs.getBytes("automatikArray", disp.automatikArray, 1 + sizeof(disp.automatikArray) * (int)( sizeof(disp.automatikArray) / sizeof(disp.automatikArray[0])));
    prefs.getBytes("autozeitArray", disp.autozeitArray, 1 + sizeof(disp.autozeitArray) * (int)( sizeof(disp.autozeitArray) / sizeof(disp.autozeitArray[0])));
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
    prefs.putUShort("intensity", disp.intensity);
    prefs.putUShort("firmwareauswahl", firmwareauswahl);
    prefs.putUShort("state", state);
    prefs.putBool("autostate", disp.autostate);
    prefs.putString("wlanpassword",disp.wlanPassword);
    prefs.putString("wlanssid",disp.wlanssid);
    prefs.putUChar("xdisplays", disp.xDisplays);
    prefs.putUChar("ydisplays", disp.yDisplays);
    prefs.putUShort("autozaehler", disp.autozaehler);
    prefs.putBytes("automatikArray", &disp.automatikArray, 1 + sizeof(&disp.automatikArray) * (int)( sizeof(&disp.automatikArray) / sizeof(&disp.automatikArray[0])));
    prefs.putBytes("autozeitArray", &disp.autozeitArray, 1 + sizeof(&disp.autozeitArray) * (int)( sizeof(&disp.autozeitArray) / sizeof(&disp.autozeitArray[0])));
}