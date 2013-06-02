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

#define N_MASK (u32) 1 << 31
#define Z_MASK (u32) 1 << 30
#define C_MASK (u32) 1 << 29
#define V_MASK (u32) 1 << 28

#define N_SET(i) ( ( i & N_MASK ) >> 31 )
#define Z_SET(i) ( ( i & Z_MASK ) >> 30 )
#define C_SET(i) ( ( i & C_MASK ) >> 29 )
#define V_SET(i) ( ( i & V_MASK ) >> 28 )

#define EQ_FLAG 0x00u
#define NE_FLAG 0x01u
#define GE_FLAG 0x0au
#define LT_FLAG 0x0bu
#define GT_FLAG 0x0cu
#define LE_FLAG 0x0du
#define AL_FLAG 0x0eu

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

inline u8 opn(u8 n, u32 instr)
{
  u8 code = (instr >> (28 - n)) & ((n << 2) - 1);
  return code;
}

u32 *arm_opr(Arm *raspi, u32 instr)
{
  u32 cprs = raspi->cprs;
  switch (instr >> 28)
  {
  case EQ_FLAG:
    if (!Z_SET(cprs))  goto next;
  case NE_FLAG:
    if ( Z_SET(cprs)) goto next;
  case GE_FLAG:
    if ( N_SET(cprs) != V_SET(cprs)) goto next;
  case LT_FLAG:
    if ( N_SET(cprs) == V_SET(cprs)) goto next;
  case GT_FLAG:
    if ( Z_SET(cprs) && ( N_SET(cprs) != V_SET(cprs))) goto next;
  case LE_FLAG:
    if (!SET_Z(cprs) && ( N_SET(cprs) == V_SET(cprs))) goto next;
  case AL_FLAG:
    goto next;
  }
  switch (instr >> 26 & 0x03)
  {
  case 0x00:
    switch (instr >> 26 & 0x07)
    {
      // long multiply
    case 0x01:
      // swap
    case 0x02:
    default: switch (instr >> 25 & 0x0F)
      {
        // multiply
      case 0x00:
        // data processing
      default:
      }
    }
    // single data transferring
  case 0x01:
  case 0x02:
    switch (instr >> 25 & 0x07)
    {
      // load/store multiple
    case 0x04:
      // branch statement
    case 0x05:
    }
  }
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
  u32 instr;
  for (;;)
  {
    execute(instr);
    decode(instr);
    instr = fetch(raspi);

  }
}

Arm *makeRaspi()
{
  // allocate and initialise the raspi struct
  Arm *raspi = (Arm *) calloc(1, sizeof(Arm));
  // allocate space for all the memory
  raspi->em = (u32 *) calloc(1, sizeof(u32) * MEMSIZE);
  raspi->dm = (u32 *) calloc(1, sizeof(u32) * MEMSIZE);
  // allocate space for all the registers
  raspi->r  = (u32 *) calloc(1, sizeof(u32) * NO_OF_REGISTERS);
  // load the contents of the file @ mempath
  return raspi;
}

int main(int argc, char **argv)
{
  char *path; switch (argc)
  {
  case 0: path = (char *)argv; break;
  case 2: path = argv[0]; break;
  default: fprintf(stderr, "No FILE provided.\n"); return NO_FILE_FOUND;
  }
  Arm *raspi = makeRaspi(path);
  loadBinaryFile(path, raspi->em);
  // begin the emulation
  fetch(raspi); decode(raspi);
  runRaspi(raspi);
  return 0;
}
