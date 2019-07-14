#include "Clock.h"
#include "WLAN.h"


const int timezone_offset_secs = 1* 60 *60;
const int dst_offset_secs = 1*60*60;

Clock::Clock()
{

}

void Clock::init() 
{
	if (WiFi.status() != WL_CONNECTED) {return;}
	// Achtung kein UTC mehr
	configTime(timezone_offset_secs, dst_offset_secs, "pool.ntp.org", "time.nist.gov");

	time_t now = time(nullptr);
}


String Clock::getTime() 
{
	char output[128];
	time_t now = time(nullptr);
	struct tm timeinfo;
	localtime_r(&now, &timeinfo);
	strftime(output, sizeof output, "%T",&timeinfo);
	return (output);
}

String Clock::getDate() 
{
	char output[128];
	time_t now = time(nullptr);
	struct tm timeinfo;
	localtime_r(&now, &timeinfo);
	strftime(output, sizeof output, "%d.%m.%y",&timeinfo);
	return (output);
}

String Clock::getWeekday() 
{
	char output[128];
	time_t now = time(nullptr);
	struct tm timeinfo;
	localtime_r(&now, &timeinfo);
	sprintf(output,"%s",weekday[timeinfo.tm_wday]);
	return (output);
}

String Clock::getMonth() 
{
	char output[128];
	time_t now = time(nullptr);
	struct tm timeinfo;
	localtime_r(&now, &timeinfo);
	sprintf(output,"%s",month[timeinfo.tm_mon]);
	return (output);
}

void Clock::setTime(uint16_t jahr,uint16_t monat, uint16_t tag, uint16_t stunde, uint16_t minute, uint16_t sekunde)
{
	struct tm tm;
	tm.tm_year = jahr - 1900;
	tm.tm_mon = monat - 1;
	tm.tm_mday = tag;
	tm.tm_hour = stunde;
	tm.tm_min = minute;
	tm.tm_sec = sekunde;
	time_t t = mktime(&tm);
	struct timeval now = { .tv_sec = t};
	settimeofday(&now, NULL);	
}

void Clock::setTime(uint32_t timestamp)
{
	time_t t = timestamp;
	struct timeval now = { .tv_sec = t};
	settimeofday(&now, NULL);	
}