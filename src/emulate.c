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

#include "emulate.h"

///////////////////////////////////////////////////////////////////////////////
// DEFINITIONS
///////////////////////////////////////////////////////////////////////////////

#define NO_OF_REGISTERS 12
#define NO_FILE_FOUND 1

// Set up program state as a C Struct
typedef struct
{
  u32 e[MEMSIZE];
  u32 d[MEMSIZE];
} Memory;

typedef struct
{
  u32 *r;        // registers
  u32 sp;        // R[13] <- stack pointer
  u32 lr;        // R[14] <- link register
  u32 pc;        // R[15] <- program counter
  u32 cpsr;      // R[16] <- flags
  u32 *em;       // encoded memory
  u32 *dm;       // decoded memory
} Arm;

static u16 lit[0x20] =
{
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
  0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
  0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
  0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
};

///////////////////////////////////////////////////////////////////////////////
// EXECUTION FUNCTIONS
///////////////////////////////////////////////////////////////////////////////

// #include "utilities/dataProcessing.c"
#include "utilities/branch.c"
#include "utilities/multiply.c"
#include "utilities/singleDataTransfer.c"
#include "utilities/binaryLoading.c"

///////////////////////////////////////////////////////////////////////////////
// DECODING FUNCTIONS
///////////////////////////////////////////////////////////////////////////////

Arm* makeRaspi(char* mempath)
{
  // allocate and initialise the raspi struct
  Arm *raspi = (Arm *) malloc(sizeof(Arm));
  // allocate space for all the memory
  raspi->em = (u32 *) malloc(sizeof(u32) * MEMSIZE);
  raspi->dm = (u32 *) malloc(sizeof(u32) * MEMSIZE);
  // allocate space for all the registers
  raspi->r  = (u32 *) malloc(sizeof(u32) * NO_OF_REGISTERS); 
  // load the contents of the file @ mempath
  loadBinaryFile(mempath, raspi->em);
  return raspi;
}

int main(int argc, char **argv)
{
  char *path;
  switch (argc)
  {
  case 0: path = (char *)argv; break;
  case 2: path = argv[0]; break;
  default: fprintf(stderr, "No FILE provided.\n"); return NO_FILE_FOUND;
  }
  Arm *raspi = makeRaspi(path);
  return 0;
}
