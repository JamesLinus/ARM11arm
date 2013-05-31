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
void dataProcessing(u32 inst)
{
  // CPRS updates still need to be implemented
  // need to find a way of not using the nexted statements
  // set up easy access to registors
  typedef arm.register[(inst >> 16) & 0x000F] operand1;
  typedef arm.register[(((inst >> 16) & 0x000F) + 1) / 2] operand2;


  // case where I = 0
  if(inst & 0x02000000 == 0)
  {
    operand2 = arm.register[inst & 0x0000000F];
    if(inst & 0x00000010)
    {
      switch((inst >> 4) & 0x00000006)
      {
        case 0:
          operand2 = operand2 << ((inst >> 7) & 0x0000003F);
          break;
        case 2:
          operand2 = operand2 >> ((inst >> 7) & 0x0000003F);
          break;
        case 4:
          break;
        case 5:
          (operand2 >> ((inst >> 7) & 0x0000003F) | 
          (operand2 << (32 - ((inst >> 7) & 0x0000003F));
          break;
      }
    }
  } else // I = 1
  {
    //convert 8 bit to 32 bit and rotate right 2* the 4 bit value specified
    operand2 = ((inst & 0x000000FF) >> ((inst >> 8) & 0x0000000F)*2)) | 
               ((inst & 0x000000FF) << (32 - ((inst >> 8) & 0x0000000F)*2));
  }
  // switch on opcodes 
  switch((inst >> 20) & 0x01e)
  {
    // rdest = and
    case 0:
      arm.register[(inst >> 12) & 0x0000F] = operand1 & operand2;
      break;
    // rdest = exclusive or
    case 2:
      arm.register[(inst >> 12) & 0x0000F] = operand1 ^ operand2;
      break;
    // sub rdes = opr1 - opr2
    case 4:
      arm.register[(inst >> 12) & 0x0000F] = operand1 - operand2;
      break;
    // rdest = opr2 - opr1
    case 6:
      arm.register[(inst >> 12) & 0x0000F] = operand2 - operand1;
      break;
    // rdest = opr1 + opr2
    case 8:
      arm.register[(inst >> 12) & 0x0000F] = operand1 + operand2;
      break;
    // opr1 & opr2
    case 16:
      operand1 & operand2;
      break;
    // opr1 xor opr2
    case 18:
      operand1 ^ operand2;
      break;
    // opr1 - opr2
    case 20:
      operand1 - operand2;
      break;
    // rdest = opr1 | opr2
    case 24:
      arm.register[(inst >> 12) & 0x0000F] = operand1 | operand2;
      break;
    // rest = opr2
    case 26:
      arm.register[(inst >> 12) & 0x0000F] = operand2;
      break;
  }
}

// problem might execute next command in pipeline before branching to new one
void branch(uint32_t inst)
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

void multiply(u32 inst)
{
  
}

void singleDataTransfer(u32 inst)
{
  
}

void processInst(u32 inst)
{
  if((inst >> 24) & 0x0F & 12 == 4)
  {
    singleDataTransfer(inst);
  } else if ((inst >> 24) & 0x0F & 12 == 8)
  {
    branch(inst);
  } else if (inst & 0x0F0000F0 == 0x00000090)
  {
    multiply(inst);
  } else
  {
    dataProcessing(inst);
  }
}

u32 decodeInstruction(u32 inst)
{
  if(inst == 0)
  {
    return 0;
  }
  u32 flags = cpsr >> 28 & 0xF;
  // verify instruction condition
  switch((inst & 0xF0000000) >> 28)
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


void main(int argc, char** argv)
{
  // grab path of binary from argvs
  char* path = argv[0];
  // initialise all struct elements to 0 
  struct arm raspi = calloc(sizeof(arm));
  struct memory m  = calloc(sizeof(memory));
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
  for(int n = 0; n < NO_OF_REGS; n++)
  {
    printf("Value of registor %d: %d/n", n, eState.registor[n]);
  }
