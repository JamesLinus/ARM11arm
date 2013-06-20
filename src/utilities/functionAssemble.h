///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: functionAssemble.h
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#ifndef FUNCTION_ASSEMBLE
#define FUNCTION_ASSEMBLE

#include "../assemble.h"

u32 assembleDataProcessing(char **args);
u32 assembleMultiply(u32 arguments, char **strings);
u32 assembleSingleDataTransfer(u32 arguments, char **strings);
u32 assembleBranch(u32 arguments, char **strings, u32 memAddr);
u32 processOp2(char* operand);

// Processes a data instructions that computes, then stores
// it's result in Rd.
static inline void processComputes(u32* binaryCode, char* rd, char* rn, char* op2)
{
  *binaryCode |= DATA_RD_SHIFT(REG(rd));
  *binaryCode |= DATA_RN_SHIFT(REG(rn));
  *binaryCode |= processOp2(op2);
  if (IS_IMMEDIATE(op2)) *binaryCode |= (1 << 25);
}

// Processes a data instruction that only has a single operand
static inline void processSingleOp(u32* binaryCode, char* rd, char* op2)
{
  *binaryCode |= DATA_RD_SHIFT(REG(rd));
  *binaryCode |= processOp2(op2);
  if (IS_IMMEDIATE(op2)) *binaryCode |= (1 << 25);
}

// Processes an instruction that sets cpsr flags
static inline void processSetsCpsr(u32* binaryCode, char* rn, char* op2)
{
  *binaryCode |= DATA_RN_SHIFT(REG(rn));
  *binaryCode |= processOp2(op2);
  if (IS_IMMEDIATE(op2)) *binaryCode |= (1 << 25);
}

#endif