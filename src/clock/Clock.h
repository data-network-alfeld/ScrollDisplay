#pragma once 

#include <Arduino.h>
#include <time.h>


class Clock
{
    public:
        Clock();
        void init();      
        String getTime();
        String getDate();
        String getWeekday();
        String getMonth();
        void setTime(uint16_t jahr,uint16_t monat, uint16_t tag, uint16_t stunde, uint16_t minute, uint16_t sekunde);
        void setTime(uint32_t timestamp);

    private:
        const char* weekday[7] 
        {
            "Sonntag",
            "Montag",
            "Dienstag",
            "Mittwoch",
            "Donnerstag",
            "Freitag",
            "Samstag"
        };
        const char* month[12]
        {
            "Januar",
            "Februar",
            "März",
            "April",
            "Mai",
            "Juni",
            "Juli",
            "August",
            "September",
            "Oktober",
            "November",
            "Dezember"
        };
};
