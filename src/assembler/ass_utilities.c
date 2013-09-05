///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: ass_utilities.c
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#include "ass_private.h"
#include <string.h>

uint32_t regToInt(char* reg)
{
  //TODO: add end pointer and error messages
  return (uint32_t)strtol(&reg[1], NULL, 0);
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

uint32_t toInt (char* integer)
{
  return (uint32_t)strtol(integer, NULL, 0);
}
