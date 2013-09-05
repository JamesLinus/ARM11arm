///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: ass_utilities.c
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#include "ass_private.h"

#define REG_D(x) (x << 16)
#define REG_N(x) (x << 12)
#define REG_S(x) (x << 8)
#define REG_M(x) (x << 0)

uint32_t regToInt(char* reg)
{
  char** endPtr;
  return (uint32_t)strtol(&reg[1], endPtr, 0);
}

uint8_t arrayContains(char* item, char** array, uint32_t arrayLen)
{
  uint32_t i;
  for(i = 0; i < arrayLen ; i++)
  {
    if(strcmp(item, array[i]) == 0)
      return 1;
  }
  return 0;
}

uint32_t toInt (char* int)
{
  char* endPtr;
  return (uint32_t)strtol(int, endPtr, 0);
}