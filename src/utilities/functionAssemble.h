///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: functionAssemble.h
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#include "res/uints.h"

// Processes a data instructions that computes, then stores
// it's result in Rd.
static inline void processComputes(u32* binaryCode, char* rd, char* rn, char* op2)
{
  *binaryCode |= DATA_RD_SHIFT(REG(rd));
  *binaryCode |= DATA_RN_SHIFT(REG(rn));
  *binaryCode |= processOp2(op2);
}

// Processes a data instruction that only has a single operand
static inline void processSingleOp(u32* binaryCode, char* rd, char* op2)
{
  *binaryCode |= DATA_RD_SHIFT(REG(rd));
  *binaryCode |= processOp2(op2);
}

// Processes an instruction that sets cpsr flags
static inline void processSetsCpsr(u32* binaryCode, char* rn, char* op2)
{
  *binaryCode |= DATA_RN_SHIFT(REG(rn));
  *binaryCode |= processOp2(op2);
}

u32 assembleDataProcessing(u32 arguments, char **strings);
u32 assembleMultiply(u32 arguments, char **strings);
u32 assembleSingleDataTransfer(u32 arguments, char **strings);
u32 assembleBranch(u32 arguments, char **strings, u32 memAddr);
