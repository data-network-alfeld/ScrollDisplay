#pragma once 

#include <Arduino.h>
#include <MD_MAX72xx.h>
#include <MD_MAXPanel.h>
#include "Configuration.h"
#include "Display.h"


class Gameoflife
{
    public:
        Gameoflife();
        void init();     
        uint32_t countCells(void);
        void firstGeneration(void);
        void nextGeneration(void);

    private:

};
