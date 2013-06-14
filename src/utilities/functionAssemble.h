///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: functionAssemble.h
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#include<stdint.h>

uint32_t assembleDataProcessing(uint32_t arguments, char **strings);

uint32_t assembleMultiply(uint32_t arguments, char **strings);

uint32_t assembleSingleDataTransfer(uint32_t arguments, char **strings);

uint32_t assembleBranch(uint32_t arguments, char **strings, uint32_t memAddr);
