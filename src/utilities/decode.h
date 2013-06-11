///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: decode.h
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#ifndef EMULATE_H
#include "../emulate.h"
#endif

#ifndef EXECUTE_H
#include "execute.h"
#endif

#ifndef DECODE_H
#define DECODE_H

u32 lsl(u32* cpsr, u32 a, u32 b, u32 set);
u32 lsr(u32* cpsr, u32 a, u32 b, u32 set);
u32 asr(u32* cpsr, u32 a, u32 b, u32 set);
u32 ror(u32* cpsr, u32 a, u32 b, u32 set);

void setShifting(Arm *raspi, u32 instr, ShiftingInstr *i);
BaseInstr *decodeInstruction(Arm *raspi, u32 index);

#endif
