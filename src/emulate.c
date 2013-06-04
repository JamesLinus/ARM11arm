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

u32 fetch(Arm *raspi)
{
  return raspi->em[raspi->pc++];
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
