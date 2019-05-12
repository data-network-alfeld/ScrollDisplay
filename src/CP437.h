#pragma once 

// CP437 conversion routines written by Frank E. Weiss (fweiss) 
// https://github.com/fweiss/badge/blob/master/src/badge/CP437.h

#include <Arduino.h>

class CP437 {
private:
protected:
    static uint16_t codes[128];
public:
    static String utf8tocp437(String utf8);
};
