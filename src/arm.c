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
#include "instructionSet.h"
#include "utilities.h"

#define NO_OF_REGS 17
#define WORDS_IN_MEMORY 65536

void processInst(uint32_t inst, uint32_t *registor, uint32_t *memory)
{
  if((inst >> 24) & 0x0F & 12 == 4)
  {
    singleDataTransfer(inst);
  } else if ((inst >> 24) & 0x0F & 12 == 8)
  {
    branch(inst);
  } else if (inst & 0xF00000F0 == 0x00000090)
  {
    multiply(inst);
  } else
  {
    dataProcessing(inst);
  }
}

uint32_t decodeInstruction(uint32_t inst, uint32_t *registor, uint32_t *memory)
{
  if(inst == 0)
  {
    return 0;
  }
  switch(inst & 0xF0000000)
  {
    case 0x00000000:
      if((registor[16] & 0xF0000000) & 4 == 4)
      {
        processInst(inst, registor, memory);
      }
      break;
    case 0x10000000:
      if((registor[16] & 0xF0000000) & 4 == 0)
      {
        processInst(inst, registor, memory);
      }
      break;
    case 0xa0000000:
      if((registor[16] & 0xF0000000) & 9 == 9 || (registor[16] & 0xF0000000) & 9 == 0)
      {
        processInst(inst, registor, memory);
      }
      break;
    case 0xb0000000:
      if((registor[16] & 0xF0000000) & 9 != 9 || (registor[16] & 0xF0000000) & 9 != 0)
      {
        processInst(inst, registor, memory);
      }
      break;
    case 0xc0000000:
     if((registor[16] & 0xF0000000) & 4 == 0 && ((registor[16] & 0xF0000000) & 9 == 9 || (registor[16] & 0xF0000000) & 9 == 0))
      {
        processInst(inst, registor, memory);
      }
      break;
    case 0xd0000000:
     if((registor[16] & 0xF0000000) & 4 == 4 && ((registor[16] & 0xF0000000) & 9 != 9 || (registor[16] & 0xF0000000) & 9 != 0))
      {
        processInst(inst, registor, memory);
      }
      break;
    case 0xe0000000:
      processInst(inst, registor, memory);
      break;
  }
  return 1;
}

void initialize(char *path)
{
  // set up state of the emulator
  struct EmulatorState
  {
    uint32_t memory[WORDS_IN_MEMORY];
    uint32_t registor[NO_OF_REGS];
  };

  // set up the pipeline state
  struct PipelineState
  {
    uint32_t decodeInst;
    uint32_t loadInst;
  };

  int loopTermination = 1;

  // initialise all struct elements to 0 
  struct EmulatorState eState = {0};
  uint32_t* loaded = loadBinaryFile(path);
  
  struct PipelineState pState = {0};

  while(loopTermination == 1)// exit on all zero input from decode
  {
    // decode the loaded instruction and execute and possibly terminate
    loopTermination = decodeInstruction(pState.loadInst, eState.registor, eState.memory);
    // load the instruction from memory
    pState.loadInst = eState.memory[eState.registor[15]];
    // increment PC
    eState.registor[15] += 4;
  }

  // print all registors to standard output
  for(int n = 0; n < NO_OF_REGS; n++)
  {
    printf("Value of registor %d: %d/n", n, eState.registor[n]);
  }
}