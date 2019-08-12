#include "WLAN.h"
#include "HTML.h"


WiFiManager wm; // global wm instance
WiFiManagerParameter text_field; 
WiFiManagerParameter animationStart_field;
WiFiManagerParameter animationEnde_field;
WiFiManagerParameter spriteStart_field;
WiFiManagerParameter spriteEnde_field;
WiFiManagerParameter pause_field;
WiFiManagerParameter intensity_field;
WiFiManagerParameter javascript_field;
WiFiManagerParameter time_field;
WiFiManagerParameter menu_field;
WiFiManagerParameter automatik_field;
WiFiManagerParameter extramenu_field;
WiFiManagerParameter select_field;

String ssid; 
String wlanpassword = "";
String allespritesString = "var allesprites=[";
String selectString = "<script>";

void selectStringGenerate()
{
    Display &disp = Display::instance();
	selectString = "<script>";
	selectString = selectString + "document.getElementById('textid').value='"+ String (disp.scrollText) +"';\n";
	selectString = selectString + "document.getElementById('animationStart').value='"+String (disp.animationStart) +"';\n";
	if (disp.animationStart == 6)
	{
		selectString = selectString + "document.getElementById('spriteStartBlock').style.display = 'block';\n";
	}
	selectString = selectString + "document.getElementById('animationEnde').value='"+ String (disp.animationEnde) +"';\n";
	if (disp.animationEnde == 6)
	{
		selectString = selectString + "document.getElementById('spriteEndeBlock').style.display = 'block';\n";
	}
	selectString = selectString + "document.getElementById('spriteStart').value='"+ String (disp.spriteStart) +"';\n";
	selectString = selectString + "spritewechsel("+String (disp.spriteStart)+",0);\n";
	selectString = selectString + "document.getElementById('spriteEnde').value='"+ String (disp.spriteEnde) +"';\n";
	selectString = selectString + "spritewechsel("+String (disp.spriteEnde)+",1);\n";
	selectString = selectString + "document.getElementById('pauseid').value='"+ String (disp.pause) +"';\n";
	selectString = selectString + "document.getElementById('intensity').value='"+ String (disp.intensity) +"';\n";
	selectString = selectString + "document.getElementById('intensityValue').innerHTML='"+ String (disp.intensity) +"';\n";
	if (disp.autostate == true) 
	{
		selectString = selectString + "document.getElementById('textAnzeige').value='99';\n";
		selectString = selectString + "document.getElementById('playlistmenuHTML').style.display = 'block';\n";
		
	} 
	else 
	{
		selectString = selectString + "document.getElementById('textAnzeige').value='"+ String (state) +"';\n";
	}
	selectString = selectString + "document.getElementById('wlanssid').value='"+ String (disp.wlanssid) +"';\n";
	selectString = selectString + "document.getElementById('wlanpassword').value='"+ String (disp.wlanPassword) +"';\n";
	selectString = selectString + "document.getElementById('xDisplays').value='"+ String (disp.xDisplays) +"';\n";
	selectString = selectString + "document.getElementById('yDisplays').value='"+ String (disp.yDisplays) +"';\n";
	selectString = selectString + "for (var i = 1; i < "+disp.autozaehler+"; i++) {\n\
		dazu();\n\
	}\n";
	for (uint8_t i = 1; i <= disp.autozaehler; i++)
	{
		selectString = selectString + "document.getElementById('automatik"+String (i)+"').value='"+String (disp.automatikArray[i])+"';\n";
		if (disp.autozeitArray[i] == 0) 
		{
			selectString = selectString + "document.getElementById('automatikzeit"+String (i)+"').value='5';\n";
		} 
		else 
		{
			selectString = selectString + "document.getElementById('automatikzeit"+String (i)+"').value='"+String (disp.autozeitArray[i])+"';\n";
		}
	}	
	selectString = selectString + "</script>";
}

String getParam(String name)
{
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
	disp.autozaehler = getParam("autozaehler").toInt();
	for (uint8_t i = 1; i <= disp.autozaehler; i++)
	{
		char tmp[16];
		sprintf(tmp,"automatik%d",i);
		disp.automatikArray[i] = getParam(tmp).toInt();
	}
	for (uint8_t i = 1; i <= disp.autozaehler; i++)
	{
		char tmp[16];
		sprintf(tmp,"automatikzeit%d",i);
		if ((getParam(tmp).toInt()) < 255 ) 
		{	
			disp.autozeitArray[i] = getParam(tmp).toInt();
		} else 
		{
			disp.autozeitArray[i] = 255;
		}
	}
	disp.scrollText = getParam("textid"); 
    disp.animationStart = getParam("animationStart").toInt();
    disp.animationEnde = getParam("animationEnde").toInt();
    disp.spriteStart = getParam("spriteStart").toInt();
    disp.spriteEnde = getParam("spriteEnde").toInt();
    disp.pause = getParam("pauseid").toInt();
    disp.intensity = getParam("intensity").toInt();
    firmwareauswahl = getParam("firmware").toInt();
	disp.parola->setIntensity(disp.intensity);
	if (WiFi.status() != WL_CONNECTED) 
	{
		clo.setTime(getParam("timestamp").toInt());
	}
	if (getParam("textAnzeige").toInt() == 99) 
	{
		disp.autostate = true;
		state = STATE::SCROLLTEXT;
	} else {
		disp.autostate = false;
		state = getParam("textAnzeige").toInt();
	}
	if (getParam("wlanpassword").length() >= 8) 
	{
		disp.wlanPassword = getParam("wlanpassword");
	}
	disp.wlanssid = getParam("wlanssid");
	disp.xDisplays = getParam("xDisplays").toInt();
    disp.yDisplays = getParam("yDisplays").toInt();

    saveConfiguration();
	selectStringGenerate();
	new (&select_field) WiFiManagerParameter(selectString.c_str());

}

uint8_t baseMac[6];
char baseMacChr[18] = {0};

void initWLAN()
{
  	Display& disp = Display::instance();

	uint8_t baseMac[6];
	// Get MAC address for WiFi station
	esp_read_mac(baseMac, ESP_MAC_WIFI_STA);
	sprintf(baseMacChr, "%02x%02x%02x%02x", baseMac[2], baseMac[3], baseMac[4], baseMac[5]);

	ssid = String("LED") + baseMacChr;
 	#ifdef CUSTOM_HOSTNAME
		ssid = CUSTOM_HOSTNAME; 
	#endif

	if (disp.wlanssid != "")
	{
		ssid = disp.wlanssid;
	}

	wm.setHostname(ssid.c_str());

	wm.setClass("invert");
	wm.setConfigPortalBlocking(false);
	wm.setEnableConfigPortal(false);

	if (wm.getWiFiIsSaved())
	{
		if (disp.wlanPassword != "") 
		{
			wlanpassword = disp.wlanPassword;
		}
		if(wm.autoConnect(ssid.c_str(), wlanpassword.c_str()))
		{
			Serial.println("Connected!");
			wm.startWebPortal();
		}
		else
		{
			Serial.println("Connect failed :( ");
		}
	}

	char tmp [2];
	for (int a = 0; a < spriteSize; a++)
	{
		if (a != 0)
		{
			allespritesString = allespritesString+",";
		}
		allespritesString = allespritesString+"['"+sprite[a].name+"',"+sprite[a].frames+","+sprite[a].width+",'";

		for (int i = 0; i < (sprite[a].frames * sprite[a].width); i++)
		{
			sprintf(tmp,"%02x",sprite[a].data[i]);
			allespritesString = allespritesString+tmp;
		}
		allespritesString = allespritesString+"']";
	}
	allespritesString = allespritesString+"];\n";
	allespritesString = allespritesString + "\
		var selectSpritestart = document.getElementById('spriteStart');\n\
		var selectSpriteende = document.getElementById('spriteEnde');\n\
		for (index in allesprites) {\n\
			selectSpritestart.options[selectSpritestart.options.length] = new Option(allesprites[index][0], index);\n\
			selectSpriteende.options[selectSpriteende.options.length] = new Option(allesprites[index][0], index);\n\
		}\n\
	";
	allespritesString = "<script>\n" + allespritesString + javascript + "</script>\n";

	int customFieldLength = 100;

	selectStringGenerate();

	new (&text_field) WiFiManagerParameter("textid", "Text", "Ferienpass 19", customFieldLength,"placeholder=\"Ferienpass 19\"");
	new (&animationStart_field) WiFiManagerParameter(animationStartHTML);
	new (&animationEnde_field) WiFiManagerParameter(animationEndeHTML);
	new (&spriteStart_field) WiFiManagerParameter(spriteStartHTML);
	new (&spriteEnde_field) WiFiManagerParameter(spriteEndeHTML);
	new (&pause_field) WiFiManagerParameter("pauseid", "Pausendauer (in ms)", "1000", customFieldLength,"placeholder=\"1000\"");
	new (&intensity_field) WiFiManagerParameter(intensityHTML);
	new (&javascript_field) WiFiManagerParameter(allespritesString.c_str());
	new (&time_field) WiFiManagerParameter(timeHTML);
	new (&menu_field) WiFiManagerParameter(menueHTML);
	new (&automatik_field) WiFiManagerParameter(automatikHTML);
	new (&extramenu_field) WiFiManagerParameter(extramenueHTML);
	new (&select_field) WiFiManagerParameter(selectString.c_str());

	wm.addParameter(&text_field);
	wm.addParameter(&animationStart_field);
	wm.addParameter(&spriteStart_field);
	wm.addParameter(&animationEnde_field);
	wm.addParameter(&spriteEnde_field);
	wm.addParameter(&pause_field);
	wm.addParameter(&intensity_field);
	wm.addParameter(&javascript_field);
	if (WiFi.status() != WL_CONNECTED) {
		wm.addParameter(&time_field);
	}
	wm.addParameter(&menu_field);
	wm.addParameter(&automatik_field);
	wm.addParameter(&extramenu_field);
	wm.addParameter(&select_field);
	wm.setSaveParamsCallback(saveParamCallback);

	std::vector<const char *> menu = {"wifi","info","param","sep","restart","exit"};
	wm.setMenu(menu);

}