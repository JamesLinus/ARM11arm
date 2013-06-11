///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: errorDump.c
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "errorDump.h"

// Small snippet to output a formatted register
void printReg(char* name, int index, u32 i)
{
  printf("    %s[\x1b[36m%2d\x1b[0m]  -  0x%08x  -  ", name, index, i);
  printBin(i, 1);
}

// Simple function to print the binary of a u32
void printBin(u32 i, int newline)
{
  for (int j = 0; j < 32; j++)
  {
    if ((i >> (32 - j - 1)) & 0x1u)
    {
      printf("%s", COL_ONE);
    }
    else
    {
      printf("0"); 
    }
  } 
  if (newline) 
  { 
    printf("\n"); 
  }
  else
  {
    printf("");
  }
}

void printTestSuite(Arm *raspi)
{
  printf("Registers:\n");
  for (int i = 0; i < 13; i++)
  {
    printf("$%-3d:%11u (0x%08x)\n",i, raspi->r[i], raspi->r[i]);
  }
  printf("PC  :%11u (0x%08x)\n", raspi->pc, raspi->pc);
  printf("CPSR:%11u (0x%08x)\n", raspi->cpsr, raspi->cpsr);
  printf("Non-zero memory:\n");
  for (int i = 0; i < MEMSIZE/4; i++)
  {
    if (raspi->em[i])
      printf("0x%08x: 0x%08x\n", 4*i, raspi->em[i]);
  }
}

// Main handler for the dump of all non-0 mem locations,
// along with all register values from R1 to R16 (inclusive of named)
void printOut(Arm *raspi)
{
  printf("\n  ============================================================================\n");
  printf("\x1b[32m");
  printf(  "  |-                      --+< ARM11 Raspi State >+--                       -|\n");
  printf("\x1b[0m");
  printf(  "  ============================================================================\n");
  printf("                   Printing state of raspi on function call.\n\n\n");
  u32 r;
  for (int i = 0; i < 12; i++)
  {
    printReg("       Register", i, raspi->r[i]);
  }
  printReg("  Stack Pointer", 13, raspi->sp);
  printReg("  Link Register", 14, raspi->lr);
  printReg("Program Counter", 15, raspi->pc);
  printReg("     CPSR Flags", 16, raspi->cpsr);
  printf("\n\n");
  printf("  +======================+==============+====================================+\n");
  printf("  |-      Mem Addr      -|-     Hex    -|-              Bin                 -|\n");
  printf("  +======================+==============+====================================+\n");
  int print = 0;
  for (int i = 0; i < MEMSIZE; i++)
  {
    if (r = raspi->em[i]) 
    {
      print = 1;
      printf("  |-   [ 0x%08x ]   -|- 0x%08x -|- ", (i << 2), r);
      printBin(r, 0); printf(" -|\n");
    }
  }
  if (print) { 
    printf("  +======================+==============+====================================+\n"); 
  }
}