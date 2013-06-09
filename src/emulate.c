///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: emulate.c
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

#include "emulate.h"
#include "utilities/execute.h"
#include "utilities/decode.h"
#include "utilities/binaryLoading.h"
#include "utilities/errorDump.h"

///////////////////////////////////////////////////////////////////////////////
// EXECUTION FUNCTIONS
///////////////////////////////////////////////////////////////////////////////

// PRE  - Given - Arm struct pointer with memory preloaded
//              - Decoded memory setup with dummy function
//              - First memory address to use for execution
// DESC - Use the decoded memory path to run the execution function after
//        making the relevant flag checks. Nothing need be known about
//        the encoded memory.
// POST - The raspi's registers and memory represent their real life
//        siblings had the same machine code been executed on a 
//        raspberry pi.
void runRaspi(Arm *raspi, int entry)
{
  BaseInstr* crrt;
  u32 *cpsr = &(raspi->cpsr);
  raspi->pc = entry;
exec:
  crrt = &(raspi->dm[raspi->pc++]);
  switch (crrt->cond)
  {
  case EQ_FLAG:
    if (Z_SET(*cpsr))  goto next;
  case NE_FLAG:
    if (!Z_SET(*cpsr)) goto next;
  case GE_FLAG:
    if ( N_SET(*cpsr) == V_SET(*cpsr)) goto next;
  case LT_FLAG:
    if ( N_SET(*cpsr) != V_SET(*cpsr)) goto next;
  case GT_FLAG:
    if (!Z_SET(*cpsr) && ( N_SET(*cpsr) == V_SET(*cpsr))) goto next;
  case LE_FLAG:
    if (Z_SET(*cpsr) || ( N_SET(*cpsr) != V_SET(*cpsr))) goto next;
  case AL_FLAG:
    goto next;
  }
  crrt->function(crrt);
next:
  if (!raspi->pc) goto fini;
  goto exec;
fini:
  printOut(raspi);
}

///////////////////////////////////////////////////////////////////////////////
// DECODING FUNCTIONS
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// UTILITY FUNCITONS
///////////////////////////////////////////////////////////////////////////////


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
    default: 
      fprintf(stderr, "No FILE provided.\n"); 
      return NO_FILE_FOUND;
  }
  Arm *raspi = makeRaspi(path);
  loadBinaryFile(path, raspi->em);
  // begin the emulation
  runRaspi(raspi,0);
  return 0;
}
