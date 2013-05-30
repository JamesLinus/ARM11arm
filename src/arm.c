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

uint32_t decodeInstruction(uint32_t loadInst)
{
  return 0;
}

void runInstruction(uint32_t loadInst)
{

}

void initialize(void)
{
  // set up state of the emulator
  struct EmulatorState
  {
    uint32_t memory[2048];
    uint32_t registor[17];
  };

  // set up the pipeline state
  struct PipelineState
  {
    uint32_t decodeInst;
    uint32_t loadInst;
  };

  // initialise all struct elements to 0 
  struct EmulatorState eState = { 0 };
  struct PipelineState pState = { 0 };
  const int NO_OF_REGS = 17;

  while(NO_OF_REGS == 17)
  {
    // run the decoded instruction
    runInstruction(pState.decodeInst);
    // decode the loaded intruction
    pState.decodeInst = decodeInstruction(pState.loadInst);
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