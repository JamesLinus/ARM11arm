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
#include "utilities.h"

#include "arm.h"

static u16 lit[0x20] = {
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
  0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
  0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
  0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
};

// OP CODE DIGEST
// 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// --Cond- 0 1 I P U 0 0 L --Rn---|--Rn--|--------Offset----------
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Cond: Condition field.
// I:  Immediate offset, if set to 1 then Offset is viewed as a
//     shifted register. If not set, then interpretted as direct
//     value.
// P:  Pre/Post indexing bit. If set, offset is summed with the base
//     register prior to the transfer, whereas if off then summed
//     once finished.
// U:  Enables or disables P on an on/off basis as you'd expect
// L:  Load or store, if on then the word is stored into memory,
//     else the word is retrieved from memory
// Rn: Base pointer for the function entry
// Rd: Source destination register for the passed word
// Offset has been covered in the above definitions.
void singleDataTransfer(u32 inst, u32 *registor, u32 *memory)
{

}

// problem might execute next command in pipeline before branching to new one
void branch(uint32_t inst, uint32_t *registor, uint32_t *memory)
{
  int32_t offset;
  if((inst >> 20) & 0x00F & 8 == 0)
  {
    offset = 0x00FFFFFF & (inst << 10) & 0xFF3FFFFF;
  } else
  {
    offset = 0xFFFFFFFF & (inst << 10);
  }
  memory[15] += offset - 2;
}

void multiply(u32 inst, u32 *registor, u32 *memory)
{
  
}

void dataProcessing(u32 inst, u32 *registor, u32 *memory)
{
  
}

void processInst(u32 inst, u32 *registor, u32 *memory)
{
  if((inst >> 24) & 0x0F & 12 == 4)
  {
    singleDataTransfer(inst, registor, memory);
  } else if ((inst >> 24) & 0x0F & 12 == 8)
  {
    branch(inst, registor, memory);
  } else if (inst & 0x0F0000F0 == 0x00000090)
  {
    multiply(inst, registor, memory);
  } else
  {
    dataProcessing(inst, registor, memory);
  }
}

u32 decodeInstruction(u32 inst, u32 *registor, u32 *memory)
{
  if(inst == 0)
  {
    return 0;
  }
  u32 flags = 0xF0000000 & registor[16];
  // verify instruction condition
  switch((inst & 0xF0000000) >> 28)
  {
    // I0, equals
    case 0x0:
    if (flags & 4 == 4)
    {
      processInst(inst, registor, memory);
    }
    break;
    // I1, not equal
    case 0x1:
    if (flags & 4 == 0)
    {
      processInst(inst, registor, memory);
    }
    break;
    // I10, greater than or equal
    case 0xa:
    if (flags & 9 == 9 || flags & 9 == 0)
    {
      processInst(inst, registor, memory);
    }
    break;
    // I11, less than
    case 0xb:
    if (flags & 9 != 9 || flags & 9 != 0)
    {
      processInst(inst, registor, memory);
    }
    break;
    // I12, greater than
    case 0xc:
    if (flags & 4 == 0 && (flags & 9 == 9 || flags & 9 == 0))
    {
      processInst(inst, registor, memory);
    }
    break;
    // I13, less than or equal
    case 0xd:
    if (flags & 4 == 4 && (flags & 9 != 9 || flags & 9 != 0))
    {
      processInst(inst, registor, memory);
    }
    break;
    // I14, always
    case 0xe:
    processInst(inst, registor, memory);
    break;
  }
  return 1;
}




void main(int argc, char** argv)
{
  // grab path of binary from argvs
  char* path = argv[0];
  // initialise all struct elements to 0 
  struct arm raspi = calloc(sizeof(arm));
  struct memory m  = calloc(sizeof(memory));
  raspi->pc = 1;
  println("Rasp! %d", raspi->pc);
  while(int j = 1; j < j;)// exit on all zero input from decode
  {
    // decode the loaded instruction and execute and possibly terminate
    loopTermination = decodeInstruction(pState.loadInst, eState.registor, eState.memory);
    // load the instruction from memory
    pState.loadInst = eState.memory[eState.registor[15]];
    // load into PC and 
    eState.registor[15] += 4;
  }

  // print all registors to standard output
  for(int n = 0; n < NO_OF_REGS; n++)
  {
    printf("Value of registor %d: %d/n", n, eState.registor[n]);
  }
}
