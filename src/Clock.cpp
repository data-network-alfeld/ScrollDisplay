#include "Clock.h"
#include <Wifi.h>


const int timezone_offset_secs = 1* 60 *60;
const int dst_offset_secs = 1*60*60;

Clock::Clock()
{

}

void Clock::init() 
{
	
	//if (WiFi.status() != WL_CONNECTED) {return;}
	// Achtung kein UTC mehr
	configTime(timezone_offset_secs, dst_offset_secs, "pool.ntp.org", "time.nist.gov");

	Serial.print(F("Waiting for NTP time sync: "));
	time_t now = time(nullptr);
	while (now < 8 * 3600 * 2) 
    {
		yield();
		delay(500);
		Serial.print(F("."));
		now = time(nullptr);
	}

	Serial.println(F(""));
	struct tm timeinfo;
	gmtime_r(&now, &timeinfo);
	Serial.print(F("Current time: "));
	Serial.print(asctime(&timeinfo));
}

String Clock::getUhrzeit() 
{
	char output[128];
	time_t now = time(nullptr);
	struct tm timeinfo;
	localtime_r(&now, &timeinfo);
	
	strftime(output, sizeof output, "%T",&timeinfo);
	return (output);
}

String Clock::getDatum() 
{
	char output[128];
	time_t now = time(nullptr);
	struct tm timeinfo;
	localtime_r(&now, &timeinfo);
	strftime(output, sizeof output, "%d.%m.%y",&timeinfo);
	return (output);
}

String Clock::getWochentag() 
{
	char output[128];
	time_t now = time(nullptr);
	struct tm timeinfo;
	localtime_r(&now, &timeinfo);
	sprintf(output,"%s",wochentag[timeinfo.tm_wday]);
	return (output);
}

String Clock::getMonat() 
{
	char output[128];
	time_t now = time(nullptr);
	struct tm timeinfo;
	localtime_r(&now, &timeinfo);
	sprintf(output,"%s",monat[timeinfo.tm_mon]);
	return (output);
}

void Clock::setUhrzeit()
{
	struct tm tm;
	tm.tm_year = 2019 - 1900;
	tm.tm_mon = 4;
	tm.tm_mday = 24;
	tm.tm_hour = 16;
	tm.tm_min = 30;
	tm.tm_sec = 0;
	time_t t = mktime(&tm);

	struct timeval now = { .tv_sec = t};
	settimeofday(&now, NULL);	

//	Serial.println(t);
	
}