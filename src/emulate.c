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

// Set up program state as a C Struct
typedef struct
{
  u32 e[MEMSIZE];
  u32 d[MEMSIZE];
} Memory;

typedef struct
{
  u32 reg[13];        // registers
  u32 sp;             // R[13] <- stack pointer
  u32 lr;             // R[14] <- link register
  u32 pc;             // R[15] <- program counter
  u32 cpsr;           // R[16] <- flags
  u32 em[MEMSIZE];    // encoded memory
  u32 dm[MEMSIZE];    // decoded memory
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

int main(int argc, char **argv)
{
  char *path;
  if (argc == 0)
  {
    // testing only from FFI
    printf("TESTING for filepath - %s\n", argv[0]);
    path = argv[0];
  }
  else if (argc != 2)
  {
    fprintf(stderr, "Path for binary file is required.\n");
    return 0;
  }
  else
  {
    path = argv[1];
  }
  // initialise raspi
  Arm *raspi = (Arm *) malloc(sizeof(Arm));
  printf("This is the pointer to the raspi %p\n", (void *)raspi);
  printf("This is the contents of em[0] - %d\n", raspi->em[0]);
  raspi->em[0] = 5;
  raspi->em[5] = 3;
  printf("This is the contents of em[0] & em[5] - %d, %d\n", raspi->em[0], raspi->em[5]);
  printf("DONE\n\n");
  // load the binary into the struct memory
  printf("This is file path %s", path);
  loadBinaryFile(path, raspi->em);
  return 0;
}
