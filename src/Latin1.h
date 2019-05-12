#pragma once 

// CP437 conversion routines written by Frank E. Weiss (fweiss) 
// https://github.com/fweiss/badge/blob/master/src/badge/CP437.h

#include <Arduino.h>

class Latin1 {
private:
protected:
    static uint16_t codes[128];
public:
    static String utf8tolatin1(String utf8);
};
