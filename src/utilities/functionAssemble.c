///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: functionAssemble.c
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#include "functionAssemble.h"
#include <assert.h>

uint32_t assembleDataProcessing(int arguments char **strings)
{
  assert (arguments >=2 && arguments <=5);
  uint32_t binaryCode = 0;
  //cond is always 1110 
  uint32_t dataProcessingCond 0xE0000000;
  //update to include condition
  binaryCode = binaryCode & dataProcessisngCond;
  //next 2 bits are 0's no matter what
  uint32_t bits26and27mask 0xF3FFFFFF;
  //update to include bits 26 and 27
  binaryCode = binaryCode & bits26and27mask;
  
  switch(arguments)
  {
    case 2:

      break;
    case 3:

      break;
    case 4:

      break;
    case 5:

      break;
  }

  return binaryCode;
}


