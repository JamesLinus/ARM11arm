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
    if (!Z_SET(*cpsr))  return 1;
  case NE_FLAG:
    if ( Z_SET(*cpsr)) return 1;
  case GE_FLAG:
    if ( N_SET(*cpsr) != V_SET(*cpsr)) return 1;
  case LT_FLAG:
    if ( N_SET(*cpsr) == V_SET(*cpsr)) return 1;
  case GT_FLAG:
    if ( Z_SET(*cpsr) && ( N_SET(*cpsr) != V_SET(*cpsr))) return 1;
  case LE_FLAG:
    if (!Z_SET(*cpsr) && ( N_SET(*cpsr) == V_SET(*cpsr))) return 1;
  case AL_FLAG:
    return 1;
  }

  return 0;
}

///////////////////////////////////////////////////////////////////////////////
// UTILITY FUNCITONS
///////////////////////////////////////////////////////////////////////////////

u32 fetch(Arm *raspi)
{
  return raspi->em[raspi->pc++];
}

void printReg(char* name, int index, u32 i)
{
  printf("  %s[%2d] - %08x - ", name, index, i);
  printBin(i);
}

void printBin(u32 i)
{
  for (int j = 0; j < 32; j++)
  {
    printf("%d", (i >> (32 - j)) & 0x1u);
  } printf("\n");  
}

void printOut(Arm *raspi)
{
  char* buff = "                     ";
  printf("%s================================\n",   buff);
  printf("%s       ARM11 Raspi State        \n",   buff);
  printf("%s================================\n\n", buff);
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
  for (int i = 0; i < MEMSIZE; i++)
  {
    if (r = raspi->em[i]) 
    {
      printf("Memory %d, %4x holds value %d, ", i, i, r);
      printBin(r);
    }
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
