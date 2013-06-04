///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: multiply_tests.c
// Group: 21
// Memebers: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "../../src/emulate.c"

int main(int argc, char **argv)
{
  u8 res = 0;
  u32 instr = (u32) atoi(argv[2]);
  Arm *raspi = makeRaspi();
  u32 *is = raspi->r;
  for (int i = 0; i < sizeof(BaseInstr)*MEMSIZE; i++)
  {
    printf("%d\n", is[i]);
  }
  // test simple multiply
  //for (int i = 0; i < 200; i++)
  //{

  //}
  return 0;
}