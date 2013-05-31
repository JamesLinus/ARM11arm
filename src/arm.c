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

uint32_t decodeInstruction(uint32_t loadInst, uint32_t *memory, uint32_t *registor)
{
  return 0;
}

void initialize(char *path)
{
  const int NO_OF_REGS = 17;
  const int WORDS_IN_MEMORY = 16384;

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

  // initialise all struct elements to 0 
  struct EmulatorState eState = { (uint32_t) 0 };
  struct PipelineState pState = { (uint32_t) 0 };

  // load bin file into memory
  eState.memory = loadBinaryFile(path);

  while(NO_OF_REGS == 17)// note change condition
  {
    // decode the loaded instruction and execute
    pState.decodeInst = decodeInstruction(pState.loadInst, eState.memory, eState.registor);
    // load the instruction from memory
    pState.loadInst = eState.memory[eState.registor[15]];
    // increment PC
    eState.registor[15]++;
  }

  // print all registors to standard output
  for(int n = 0; n < NO_OF_REGS; n++)
  {
    printf("Value of registor %d: %d/n", n, eState.registor[n]);
  }
}