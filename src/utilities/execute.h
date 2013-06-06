///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: execute.h
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#ifndef EMULATE_H
#include "../emulate.h"
#endif

#ifndef EXECUTE_H
#define EXECUTE_H

void setflags(u32* cpsr, u32 result);
void setCflag(u32* cpsr, u32 carryOut);

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

#endif
