///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: execute.h
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#ifndef EXECUTE_H
#define EXECUTE_H

#include "../emulate.h"

// Declared in header due to static
static inline void setflags(u32* cpsr, u32 result)
{
  // set the N flag
  *(cpsr) |= (result & N_MASK);
  // if the result indicates...
  if (!result)
  { // turn Z on
    *cpsr |= Z_MASK; return;
  } // else turn Z off
  *cpsr &= ~Z_MASK;
}

static inline void setCflag(u32* cpsr, u32 carryOut)
{
  *cpsr &= ~C_MASK; 
  *cpsr |= (carryOut << 29);
}

void branch(PtrToBeCast base);
void singleDataTransfer(PtrToBeCast base);
void multiply(PtrToBeCast base);
void dataProcessingInstruction(PtrToBeCast base);

void and(PtrToBeCast base);
void eor(PtrToBeCast base);
void sub(PtrToBeCast base);
void rsb(PtrToBeCast base);
void add(PtrToBeCast base);
void tst(PtrToBeCast base);
void teq(PtrToBeCast base);
void cmp(PtrToBeCast base);
void orr(PtrToBeCast base);
void mov(PtrToBeCast base);

void terminate(PtrToBeCast base);

#endif
