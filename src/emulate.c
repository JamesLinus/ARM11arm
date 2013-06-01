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
#include <ctype.h>
#include "utilities.h"

#include "emulate.h"

// UTILITY FUNCTIONS
#include "utilities/dataProcessing.c"
#include "utilities/branch.c"
#include "utilities/multiply.c"
#include "utilities/singleDataTransfer"
#include "utilities/binaryLoading.c"

static u16 lit[0x20] =
{
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
  0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
  0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
  0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
};

void processInst(u32 inst)
{
  if ((inst >> 24) & 0x0F & 12 == 4)
  {
    singleDataTransfer(inst);
  }
  else if ((inst >> 24) & 0x0F & 12 == 8)
  {
    branch(inst);
  }
  else if (inst & 0x0F0000F0 == 0x00000090)
  {
    multiply(inst);
  }
  else
  {
    dataProcessing(inst);
  }
}

u32 decodeInstruction(u32 inst)
{
  if (inst == 0)
  {
    return 0;
  }
  u32 flags = cpsr >> 28 & 0xF;
  // verify instruction condition
  switch ((inst & 0xF0000000) >> 28)
  {
    // I0, equals
  case 0x00:
    if (flags & 4 == 4)
    {
      processInst(inst);
    }
    break;
    // I1, not equal
  case 0x1:
    if (flags & 4 == 0)
    {
      processInst(inst);
    }
    break;
    // I10, greater than or equal
  case 0xa:
    if (flags & 9 == 9 || flags & 9 == 0)
    {
      processInst(inst);
    }
    break;
    // I11, less than
  case 0xb:
    if (flags & 9 != 9 || flags & 9 != 0)
    {
      processInst(inst);
    }
    break;
    // I12, greater than
  case 0xc:
    if (flags & 4 == 0 && (flags & 9 == 9 || flags & 9 == 0))
    {
      processInst(inst);
    }
    break;
    // I13, less than or equal
  case 0xd:
    if (flags & 4 == 4 && (flags & 9 != 9 || flags & 9 != 0))
    {
      processInst(inst);
    }
    break;
    // I14, always
  case 0xe:
    processInst(inst);
    break;
  }
  return 1;
}


void main(int argc, char **argv)
{
  // grab path of binary from argvs
  char *path = argv[0];
  // initialise all struct elements to 0
  struct Arm *raspi = calloc(1, sizeof(Arm));
  struct Memory *m  = calloc(1, sizeof(Memory));
  // load the binary into the struct memory
  loadBinaryFile(path, raspi->m);
  printf('Hello');
  return 0;
}

void run_arm(struct arm *raspi)
{
  // EXECUTE
  *(raspi->pc)
  // get instruction from memory
  // decode instruction
  // execute instruction
}

// print all registors to standard output
for (int n = 0; n < NO_OF_REGS; n++)
{
  printf("Value of registor %d: %d/n", n, eState.registor[n]);
}
