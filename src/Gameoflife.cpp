#include "Gameoflife.h"
#include "Display.h"

#ifndef _disp_
#define _disp_
	Display& dispa = Display::instance();
#endif

//  MD_MAXPanel dispa.max72xx = dispa.dispa.max72xx;

//        int xMax = dispa.max72xx.getXMax();
//        int yMax = dispa.max72xx.getYMax();

Gameoflife::Gameoflife()
{
    
}


void Gameoflife::init() 
{
//    Display& disp = Display::instance();
//    MD_MAXPanel dispa.max72xx = disp.dispa.max72xx;
//   	this->dispa.max72xx = dispa.max72xx;
}

uint32_t Gameoflife::countCells(void)
{
  uint32_t count = 0;

  for (uint16_t x = 0; x <= dispa.max72xx.getXMax(); x++)
    for (uint16_t y = 0; y <= dispa.max72xx.getYMax(); y++)
      count += (dispa.max72xx.getPoint(x,y) ? 1:0);

  return(count);
}

void Gameoflife::firstGeneration(void)
// Create a 4-way symmetric random setup
{
  dispa.max72xx.update(false);

  Serial.println("\n-- FIRST Generation");
  Serial.printf("\n-- Field size (%d,%d) - ", dispa.max72xx.getXMax() - 1, dispa.max72xx.getYMax() - 1);
  dispa.max72xx.clear();
  for (uint16_t x=1; x<(dispa.max72xx.getXMax()+1) / 2; x++)
    for (uint16_t y = 1; y < (dispa.max72xx.getYMax()+1) / 2; y++)
    {
      bool b = (random(101) > 50);

      dispa.max72xx.setPoint(x, y, b);
      dispa.max72xx.setPoint(dispa.max72xx.getXMax() - x, y, b);
      dispa.max72xx.setPoint(x, dispa.max72xx.getYMax() - y, b);
      dispa.max72xx.setPoint(dispa.max72xx.getXMax() - x, dispa.max72xx.getYMax() - y, b);
    }
      
  dispa.max72xx.update(true);
}

void Gameoflife::nextGeneration(void)
// Apply the rules
{
  bool rowBuf[2][dispa.max72xx.getXMax()+2];
  uint16_t count;
  bool newCell;

  Serial.println("\n-- NEW generation");
  // clear out the row buffers
  memset(rowBuf, 0, sizeof(rowBuf));
  dispa.max72xx.update(false);
  
  for (uint16_t y=dispa.max72xx.getYMax()-1; y>=1; y--)
  {
    // copy the current row to the buffer
    for (uint16_t x=0; x<dispa.max72xx.getXMax(); x++)
      rowBuf[1][x] = dispa.max72xx.getPoint(x, y);

    // work out a 'new' current row
    for (uint16_t x=1; x<dispa.max72xx.getXMax(); x++)
    {
      // count the number of neighbours
      count = rowBuf[0][x-1] ? 1:0;
      count += rowBuf[0][x]  ? 1:0;
      count += rowBuf[0][x+1]? 1:0;
      count += rowBuf[1][x-1]? 1:0;
      count += rowBuf[1][x+1]? 1:0;
      count += dispa.max72xx.getPoint(x-1, y-1)? 1:0;
      count += dispa.max72xx.getPoint(x, y-1)  ? 1:0;
      count += dispa.max72xx.getPoint(x+1, y-1)? 1:0;

      Serial.printf("\n%d %d", x, y);
      Serial.printf(" count=%d", count);
      Serial.print(" ->");
      
      if (count < 2)
      {
        // A live cell with fewer than two neighbors dies.
        newCell = false;
        Serial.print("dies.");
      }
      else if ((count == 2 || count == 3) && dispa.max72xx.getPoint(x, y))
      {
        // A live cell with two or three neighbors lives on.
        newCell = true;
        Serial.print("stays.");
      }
      else if (count == 3 && !dispa.max72xx.getPoint(x, y))
      {
        // A dead cell with exactly three neighbors becomes live.
        newCell = true;
        Serial.print("born.");
      }
      else
      {
        // A live cell with more than three neighbors dies.
        newCell = false;
        Serial.print("dies.");
      }

      dispa.max72xx.setPoint(x, y, newCell);
    }

    // update the saved row buffers
    for (uint16_t x=0; x<=dispa.max72xx.getXMax(); x++)
      rowBuf[0][x] = rowBuf[1][x];
  }

  dispa.max72xx.update(true);
}