#pragma once 

#include <Arduino.h>
#include <time.h>


class Clock
{
    public:
        Clock();
        void init();      
        String getUhrzeit();
        String getDatum();
        String getWochentag();
        String getMonat();
        void setUhrzeit();

    private:
        const char* wochentag[7] 
        {
            "Sonntag",
            "Montag",
            "Dienstag",
            "Mittwoch",
            "Donnerstag",
            "Freitag",
            "Samstag"
        };
        const char* monat[12]
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
