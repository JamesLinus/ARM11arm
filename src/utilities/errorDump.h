///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: errorDump.h
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#ifndef EMULATE_H
#include "../emulate.h"
#endif

#ifndef ERROR_DUMP_H
#define ERROR_DUMP_H

#define COL_ONE "\x1b[1;36m1\x1b[0m"

void printReg(char* name, int index, u32 i);
void printBin(u32 i, int newline);
void printOut(Arm *raspi);

#endif
