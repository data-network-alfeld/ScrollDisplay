#include "Gameoflife.h"
#include "Display.h"

Gameoflife::Gameoflife()
{
    
}


void Gameoflife::init() 
{
//    Display& disp = Display::instance();
//    MD_MAXPanel max72xx = disp.max72xx;
//   	this->max72xx = max72xx;
}

uint32_t Gameoflife::countCells(void)
{
    Display& disp = Display::instance();
    MD_MAXPanel max72xx = disp.max72xx;

  uint32_t count = 0;

  for (uint16_t x = 0; x <= xMax; x++)
    for (uint16_t y = 0; y <= yMax; y++)
      count += (max72xx.getPoint(x,y) ? 1:0);

  return(count);
}

void Gameoflife::firstGeneration(void)
// Create a 4-way symmetric random setup
{
    Display& disp = Display::instance();
    MD_MAXPanel max72xx = disp.max72xx;

  max72xx.update(false);

  Serial.println("\n-- FIRST Generation");
  Serial.printf("\n-- Field size (%d,%d) - ", xMax - 1, yMax - 1);
  max72xx.clear();
  for (uint16_t x=1; x<(xMax+1) / 2; x++)
    for (uint16_t y = 1; y < (yMax+1) / 2; y++)
    {
      bool b = (random(101) > 50);

      max72xx.setPoint(x, y, b);
      max72xx.setPoint(xMax - x, y, b);
      max72xx.setPoint(x, yMax - y, b);
      max72xx.setPoint(xMax - x, yMax - y, b);
    }
      
  max72xx.update(true);
}

void Gameoflife::nextGeneration(void)
// Apply the rules
{
    Display& disp = Display::instance();
    MD_MAXPanel max72xx = disp.max72xx;

  bool rowBuf[2][xMax+2];
  uint16_t count;
  bool newCell;

  Serial.println("\n-- NEW generation");
  // clear out the row buffers
  memset(rowBuf, 0, sizeof(rowBuf));
  max72xx.update(false);
  
  for (uint16_t y=yMax-1; y>=1; y--)
  {
    // copy the current row to the buffer
    for (uint16_t x=0; x<xMax; x++)
      rowBuf[1][x] = max72xx.getPoint(x, y);

    // work out a 'new' current row
    for (uint16_t x=1; x<xMax; x++)
    {
      // count the number of neighbours
      count = rowBuf[0][x-1] ? 1:0;
      count += rowBuf[0][x]  ? 1:0;
      count += rowBuf[0][x+1]? 1:0;
      count += rowBuf[1][x-1]? 1:0;
      count += rowBuf[1][x+1]? 1:0;
      count += max72xx.getPoint(x-1, y-1)? 1:0;
      count += max72xx.getPoint(x, y-1)  ? 1:0;
      count += max72xx.getPoint(x+1, y-1)? 1:0;

      Serial.printf("\n%d %d", x, y);
      Serial.printf(" count=%d", count);
      Serial.print(" ->");
      
      if (count < 2)
      {
        // A live cell with fewer than two neighbors dies.
        newCell = false;
        Serial.print("dies.");
      }
      else if ((count == 2 || count == 3) && max72xx.getPoint(x, y))
      {
        // A live cell with two or three neighbors lives on.
        newCell = true;
        Serial.print("stays.");
      }
      else if (count == 3 && !max72xx.getPoint(x, y))
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

      max72xx.setPoint(x, y, newCell);
    }

    // update the saved row buffers
    for (uint16_t x=0; x<=xMax; x++)
      rowBuf[0][x] = rowBuf[1][x];
  }

  max72xx.update(true);
}