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
  // assign variables that will keep swapping,
  // thus avoiding repeated assignment overhead
  BaseInstr* crrt;  // the current instruction
  // a pointer to the cpsr register for convenience
  u32 *cpsr = &(raspi->cpsr);
  // set the program counter to the given entry point
  raspi->pc = entry;
  printf("\nStart exec!!\n\n");
  // view from hereon out as the 'execution' stage
exec:
  // fetch the current instruction
  crrt = &(raspi->dm[raspi->pc++]);
  // switch on the current instructions condition
  // if it in any way doesn't satisfy the conditions, then
  // jump to the next label- avoid execution of this instruction
  // entirely
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
    if ( Z_SET(*cpsr) || ( N_SET(*cpsr) != V_SET(*cpsr))) goto next;
  case AL_FLAG:
    goto next;
  } 
  // if we pass the condition checks, then proceed to
  // call the function saved into the base instr struct
  crrt->function(crrt);
next:
  // if at any point we hit halt, then the halting function
  // will have been called and therefore the cpsr flags should
  // be set to all 0's. If this is the case, then __finish__
  if (!raspi->halt) goto fini;
  // else jump back to execution
  goto exec;
fini:
  // on finish, dump the current raspberry pi registers and
  // non-zero memory location/value pairs
  printOut(raspi);
}

///////////////////////////////////////////////////////////////////////////////
// DECODING FUNCTIONS
///////////////////////////////////////////////////////////////////////////////

// ALSO AN EXECUTE FUNCTION - REQUIRED!!!
// PRE  - Given an Arm pointer with loaded memory
//        An entry point from whence to begin the decode
// DESC - Decode all encoded memory indexes from the entry
//        point to (and including) the next branch statement
// POST - All decoded memory from the entry to the next branch will be
//        decoded, replaced with their BaseInstr representations 
void decodeTillBranch(PtrToBeCast base)
{
  // i will be the empty instruction pointer
  EmptyInstr* i = (EmptyInstr*) base;
  // j will be the iterative measure
  int j = i->entry;
  // raw will represent the current unprocessed instruction
  u32 raw = i->raspi->em[j]; 
  do
  {
    // fetch next instr (for branch check only, should change this)
    raw = i->raspi->em[j];
    // decode the instruction, save into dm[j]
    decodeInstruction(i->raspi, j);
  } while (!IS_BRANCH(raw) && j < MEMSIZE - 1 && (raw = i->raspi->em[j++]));  
  // decode only while not branch
}

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
  for (int i = 0; i < MEMSIZE; i++)
  {
    // cast to the empty instruction type for initialization
    EmptyInstr* instr = (EmptyInstr*) &(raspi->dm[i]);
    // make the function point to the decodeTillBranch
    instr->function = &decodeTillBranch;
    // assign entry the value of the current array index
    instr->entry = i;
  }
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
