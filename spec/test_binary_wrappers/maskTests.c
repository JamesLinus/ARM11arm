///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: masking_tests.c
// Group: 21
// Memebers: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../../src/emulate.h"
#include "../../src/utilities/opstructs.h"
#include "../../src/definitions.h"

int main(int argc, char** argv)
{
  u8 res = 0;
  u32 instr = (u32) atoi(argv[2]);
  if (*(argv[1]) == 'D')
  {
    res = IS_DATA(instr);
  }
  else if (*(argv[1]) == 'M')
  {
    res = IS_MUL(instr);
  }
  else if (*(argv[1]) == 'S')
  {
    res = IS_S_DATA(instr);
  }
  else if (*(argv[1]) == 'B')
  {
    res = IS_BRANCH(instr);
  }
  printf("%d",res);
  return 0;
}