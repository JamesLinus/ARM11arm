///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: emulate.c
// Group: 21
// Memebers: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

#include "emulate.h"
#include "utilities/execute.h"
#include "utilities/decode.h"
#include "utilities/binaryLoading.h"

///////////////////////////////////////////////////////////////////////////////
// EXECUTION FUNCTIONS
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// DECODING FUNCTIONS
///////////////////////////////////////////////////////////////////////////////

int checkFlags(u32 *cpsr, u8 cond)
{
  switch (cond)
  {
  case EQ_FLAG:
    if (!Z_SET(*cpsr))  goto next;
  case NE_FLAG:
    if ( Z_SET(*cpsr)) goto next;
  case GE_FLAG:
    if ( N_SET(*cpsr) != V_SET(*cpsr)) goto next;
  case LT_FLAG:
    if ( N_SET(*cpsr) == V_SET(*cpsr)) goto next;
  case GT_FLAG:
    if ( Z_SET(*cpsr) && ( N_SET(*cpsr) != V_SET(*cpsr))) goto next;
  case LE_FLAG:
    if (!Z_SET(*cpsr) && ( N_SET(*cpsr) == V_SET(*cpsr))) goto next;
  case AL_FLAG:
    goto next;
  }
next:
  // this on as yet not implemented opcode
  return 0;
}

///////////////////////////////////////////////////////////////////////////////
// UTILITY FUNCITONS
///////////////////////////////////////////////////////////////////////////////

inline u32 MEMGET(Arm *raspi, u32 index) { return raspi->em[index]; }
//inline u32 MEMSET(Arm *raspi, u32 index, )

u32 fetch(Arm *raspi)
{
  return raspi->em[raspi->pc++];
}

void printReg(char* name, int index, u32 i)
{
  printf("    %s[\x1b[36m%2d\x1b[0m]  -  0x%08x  -  ", name, index, i);
  printBin(i, 1);
}

#define COL_ONE "\x1b[1;36m1\x1b[0m"

inline void printBin(u32 i, int newline)
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
    printReg("       Register", i+1, raspi->r[i]);
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
      printf("  |-   [ 0x%08x ]   -|- 0x%08x -|- ", i, r);
      printBin(r, 0); printf(" -|\n");
    }
  }
  if (print) { 
    printf("  +======================+==============+====================================+\n"); 
  }
}

int runRaspi(Arm *raspi)
{
  //u32 instr;
  /*
  emulate:
  execute(instr);
  decode(instr);
  instr = fetch(raspi);
  goto emulate
  stackprint:
  */
  return 0;
}

Arm *makeRaspi()
{
  // allocate and initialise the raspi struct
  Arm *raspi = (Arm *) calloc(1, sizeof(Arm));
  // allocate space for all the memory
  raspi->em = (u32 *) calloc(1, sizeof(u32) * MEMSIZE);
  raspi->dm = (BaseInstr *) calloc(1, sizeof(BaseInstr) * MEMSIZE);
  // allocate space for all the registers
  raspi->r  = (u32 *) calloc(1, sizeof(u32) * NO_OF_REGISTERS);
  // load the contents of the file @ mempath
  return raspi;
}

int main(int argc, char **argv)
{
  char *path; switch (argc)
  {
    // case 0 for testing purposes
  case 0: path = (char *)argv; break;
  case 2: path = argv[0]; break;
  default: fprintf(stderr, "No FILE provided.\n"); return NO_FILE_FOUND;
  }
  Arm *raspi = makeRaspi(path);
  loadBinaryFile(path, raspi->em);
  // begin the emulation
  return runRaspi(raspi);
}
