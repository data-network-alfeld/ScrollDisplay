#include "Filesystem.h"

String file_get_contents(String filename)
{
    if(!SPIFFS.begin(true)){
        Serial.println("SPIFFS Mount Failed");
        return "spiffs error";
    }

	String result;
	File file = SPIFFS.open("/" + filename + ".txt");
	if(!file || file.isDirectory())
	{
	    return "";
	}

    result = file.readString(); 
    file.close();
    return result; 
}

bool file_put_contents(String filename, String content)
{
    File file = SPIFFS.open("/" + filename + ".txt", "w");
	if(!file)
	{
	    return false; 
	}
    file.print(content);

    return true;
}

void readConfiguration()
{
    Display& disp = Display::instance();

    disp.scrollText = file_get_contents("text"); 
    disp.animation = file_get_contents("animation").toInt();
    disp.pause = file_get_contents("pause").toInt();

    disp.intensity = file_get_contents("intensity").toInt();
    disp.parola.setIntensity(disp.intensity);
}

void saveConfiguration()
{
    Display& disp = Display::instance();
    file_put_contents("text", disp.scrollText);
    file_put_contents("animation", String(disp.animation));
    file_put_contents("pause", String(disp.pause));
}