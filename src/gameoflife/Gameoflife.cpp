#include "Gameoflife.h"

Gameoflife::Gameoflife()
{
    
}


void Gameoflife::init() 
{

}

uint32_t Gameoflife::countCells(void)
{
	Display& disp = Display::instance();
  uint32_t count = 0;

  for (uint16_t x = 0; x <= disp.maxPan->getXMax(); x++)
    for (uint16_t y = 0; y <= disp.maxPan->getYMax(); y++)
      count += (disp.maxPan->getPoint(x,y) ? 1:0);

  return(count);
}

void Gameoflife::firstGeneration(void)
// Create a 4-way symmetric random setup
{
  Display& disp = Display::instance();
  disp.maxPan->update(false);

//  Serial.println("\n-- FIRST Generation");
//  Serial.printf("\n-- Field size (%d,%d) - ", disp.maxPan->getXMax() - 1, disp.maxPan->getYMax() - 1);
  disp.maxPan->clear();
  for (uint16_t x=1; x<(disp.maxPan->getXMax()+1) / 2; x++)
    for (uint16_t y = 1; y < (disp.maxPan->getYMax()+1) / 2; y++)
    {
      bool b = (random(101) > 50);

      disp.maxPan->setPoint(x, y, b);
      disp.maxPan->setPoint(disp.maxPan->getXMax() - x, y, b);
      disp.maxPan->setPoint(x, disp.maxPan->getYMax() - y, b);
      disp.maxPan->setPoint(disp.maxPan->getXMax() - x, disp.maxPan->getYMax() - y, b);
    }
      
  disp.maxPan->update(true);
}

void Gameoflife::nextGeneration(void)
// Apply the rules
{
  Display& disp = Display::instance();
  bool rowBuf[2][disp.maxPan->getXMax()+2];
  uint16_t count;
  bool newCell;

//  Serial.println("\n-- NEW generation");
  // clear out the row buffers
  memset(rowBuf, 0, sizeof(rowBuf));
  disp.maxPan->update(false);
  
  for (uint16_t y=disp.maxPan->getYMax()-1; y>=1; y--)
  {
    // copy the current row to the buffer
    for (uint16_t x=0; x<disp.maxPan->getXMax(); x++)
      rowBuf[1][x] = disp.maxPan->getPoint(x, y);

    // work out a 'new' current row
    for (uint16_t x=1; x<disp.maxPan->getXMax(); x++)
    {
      // count the number of neighbours
      count = rowBuf[0][x-1] ? 1:0;
      count += rowBuf[0][x]  ? 1:0;
      count += rowBuf[0][x+1]? 1:0;
      count += rowBuf[1][x-1]? 1:0;
      count += rowBuf[1][x+1]? 1:0;
      count += disp.maxPan->getPoint(x-1, y-1)? 1:0;
      count += disp.maxPan->getPoint(x, y-1)  ? 1:0;
      count += disp.maxPan->getPoint(x+1, y-1)? 1:0;

    	delay(1);

//      Serial.printf("\n%d %d", x, y);
//      Serial.printf(" count=%d", count);
//      Serial.print(" ->");
      
      if (count < 2)
      {
        // A live cell with fewer than two neighbors dies.
        newCell = false;
//        Serial.print("dies.");
      }
      else if ((count == 2 || count == 3) && disp.maxPan->getPoint(x, y))
      {
        // A live cell with two or three neighbors lives on.
        newCell = true;
//        Serial.print("stays.");
      }
      else if (count == 3 && !disp.maxPan->getPoint(x, y))
      {
        // A dead cell with exactly three neighbors becomes live.
        newCell = true;
//        Serial.print("born.");
      }
      else
      {
        // A live cell with more than three neighbors dies.
        newCell = false;
//        Serial.print("dies.");
      }

      disp.maxPan->setPoint(x, y, newCell);
    }

    // update the saved row buffers
    for (uint16_t x=0; x<=disp.maxPan->getXMax(); x++)
      rowBuf[0][x] = rowBuf[1][x];
  }

  disp.maxPan->update(true);
}