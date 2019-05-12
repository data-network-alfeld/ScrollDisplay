#include "WLAN.h"
#include "HTML.h"

WiFiManager wm; // global wm instance
WiFiManagerParameter text_field; 
WiFiManagerParameter animation_field;
WiFiManagerParameter pause_field;

String ssid; 

String getParam(String name){
  //read parameter from server, for customhmtl input
  String value;
  if(wm.server->hasArg(name)) {
    value = wm.server->arg(name);
  }
  return value;
}

void saveParamCallback(){
  Serial.println("PARAM textid = " + getParam("textid"));
  Serial.println("PARAM animation = " + getParam("animation"));
  Serial.println("PARAM pauseid = " + getParam("pauseid"));
}

void initWLAN()
{
    ssid = String("LED") + String(WIFI_getChipId(),HEX);

	wm.setClass("invert");
	wm.setConfigPortalBlocking(false);
	wm.setConfigPortalTimeout(300);

	if (wm.getWiFiIsSaved())
	{
		if(wm.autoConnect())
		{
			Serial.println("Connected!");
		}
		else
		{
			Serial.println("Connect failed :( ");
		}
	}
	
	int customFieldLength = 100;
	
	new (&text_field) WiFiManagerParameter("textid", "Text", "Hallo Welt!", customFieldLength,"placeholder=\"Hallo Welt!\"");
	new (&animation_field) WiFiManagerParameter(animationHTML);
	new (&pause_field) WiFiManagerParameter("pauseid", "Pausendauer (in ms)", "1000", customFieldLength,"placeholder=\"1000\"");

	wm.addParameter(&text_field);
	wm.addParameter(&animation_field);
	wm.addParameter(&pause_field);

	wm.setSaveParamsCallback(saveParamCallback);

	std::vector<const char *> menu = {"wifi","info","param","sep","restart","exit"};
	wm.setMenu(menu);

}