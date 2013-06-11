///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: emulate.h
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#ifndef EMULATE_H
#define EMULATE_H

#include <stdint.h>

#define NO_OF_REGS 16
#define MEMSIZE 65536

typedef uint8_t   u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#include "res/opstructs.h"
#include "res/definitions.h"

// Set up program state as a C Struct
typedef struct
{
  u32 e[MEMSIZE];
  u32 d[MEMSIZE];
} Memory;

typedef struct
{
  u32 *r;        // registers
  u32 sp;        // R[13] <- stack pointer
  u32 lr;        // R[14] <- link register
  u32 pc;        // R[15] <- program counter
  u32 cpsr;      // R[16] <- flags
  u32 *em;           // encoded memory
  BaseInstr *dm;       // decoded memory
  u8  halt;      // a specific halting flag
} Arm;

typedef struct
{
  BASE
  int entry;
  Arm* raspi;
} EmptyInstr;

static inline u32 _memget(u8 *mem, u32 addr)
{
  u8 *picker = mem + addr;
  u32 *word  = (u32*) picker;
  return *word; 
}

static inline void _memset(u8 *mem, u32 addr, u32 val)
{
  u8 *picker = mem + addr;
  u32 *word  = (u32*) picker;
  *word = val;
}

int checkFlags(u32* cpsr, u8 cond);
u32 fetch(Arm *raspi);
void runRaspi(Arm *raspi, int entry, int suppress);
Arm *makeRaspi();
int main(int argc, char **argv);
void printBin(u32 i, int newline);
void printOut(Arm *raspi);

#endif
