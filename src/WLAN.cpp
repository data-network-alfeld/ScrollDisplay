#include "WLAN.h"
#include "HTML.h"

WiFiManager wm; // global wm instance
WiFiManagerParameter text_field; 
WiFiManagerParameter animationStart_field;
WiFiManagerParameter animationEnde_field;
WiFiManagerParameter spriteStart_field;
WiFiManagerParameter spriteEnde_field;
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

void saveParamCallback()
{
    Display& disp = Display::instance();
    disp.scrollText = getParam("textid"); 
    disp.animationStart  = getParam("animationStart").toInt();
    disp.animationEnde  = getParam("animationEnde").toInt();
    disp.spriteStart  = getParam("spriteStart").toInt();
    disp.spriteEnde  = getParam("spriteEnde").toInt();
    disp.pause      = getParam("pauseid").toInt();

    saveConfiguration();
}

void initWLAN()
{
  ssid = String("LED") + String(WIFI_getChipId(),HEX);

	#ifdef CUSTOM_HOSTNAME
		ssid = CUSTOM_HOSTNAME; 
	#endif

	wm.setHostname(ssid.c_str());

	wm.setClass("invert");
	wm.setConfigPortalBlocking(false);
	wm.setEnableConfigPortal(false);

	if (wm.getWiFiIsSaved())
	{
		if(wm.autoConnect(ssid.c_str(), NULL))
		{
			Serial.println("Connected!");
			wm.startWebPortal();
		}
		else
		{
			Serial.println("Connect failed :( ");
		}
	}
	
	
	int customFieldLength = 100;
	
	new (&text_field) WiFiManagerParameter("textid", "Text", "Ferienpass 19", customFieldLength,"placeholder=\"Ferienpass 19\"");
	new (&animationStart_field) WiFiManagerParameter(animationStartHTML);
	new (&animationEnde_field) WiFiManagerParameter(animationEndeHTML);
	new (&spriteStart_field) WiFiManagerParameter(spriteStartHTML);
	new (&spriteEnde_field) WiFiManagerParameter(spriteEndeHTML);
	new (&pause_field) WiFiManagerParameter("pauseid", "Pausendauer (in ms)", "1000", customFieldLength,"placeholder=\"1000\"");

	wm.addParameter(&text_field);
	wm.addParameter(&animationStart_field);
	wm.addParameter(&animationEnde_field);
	wm.addParameter(&spriteStart_field);
	wm.addParameter(&spriteEnde_field);
	wm.addParameter(&pause_field);

	wm.setSaveParamsCallback(saveParamCallback);

	std::vector<const char *> menu = {"wifi","info","param","sep","restart","exit"};
	wm.setMenu(menu);

}