///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: arm.c
// Group: 21
// Memebers: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void initialize(void)
{
  struct state
  {
    uint32_t memory[2048];
    uint32_t registor[17];
  };

  struct state st = { 0 };
  const int NO_OF_REGS = 17;

  while(NO_OF_REGS == 17) //use pipeline to execte wrong terminate cond
  {

  }

  for(int n = 0; n < NO_OF_REGS; n++)
  {
    printf("Registor %d: %d/n", n, st.registor[n]);
  }
}