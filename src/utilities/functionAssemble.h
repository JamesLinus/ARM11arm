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

u32 assembleDataProcessing(u32 arguments, char **strings);
u32 assembleMultiply(u32 arguments, char **strings);
u32 assembleSingleDataTransfer(u32 arguments, char **strings);
u32 assembleBranch(u32 arguments, char **strings, u32 memAddr);
u32 processOp2(char* operand);

const char *operands[] = {
  "and", "eor", "sub", "rsb", 
  "add", "adc", "sbc", "rsc", 
  "tst", "teq", "cmp", "cmn", 
  "orr", "mov", "bic", "mvn",
};

const int operandType[] = {
  COMPUTES,  COMPUTES,  COMPUTES,  COMPUTES,
  COMPUTES,  COMPUTES,  COMPUTES,  COMPUTES,
  SETS_CPSR, SETS_CPSR, SETS_CPSR, SETS_CPSR,
  COMPUTES,  SINGLE_OP_ASSIGNS, 0, 0, // TODO- Support bic and mvn
};

const int setcond[] = {
  1, 1, 1, 1,
  1, 1, 1, 1,
  0, 0, 0, 1,
  1, 1, 1, 1,
};

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

#endif