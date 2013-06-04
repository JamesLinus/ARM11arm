///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: execute.h
// Group: 21
// Memebers: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#ifndef EMULATE_H
#include "../emulate.h"
#endif

#ifndef EXECUTE_H
#define EXECUTE_H

void branch(PtrToBeCast base);
void singleDataTransfer(PtrToBeCast *base);
void multiply(Arm *raspi, BaseInstr *i);

#endif