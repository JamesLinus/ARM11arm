///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: opstructs.h
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#ifndef EMULATE_H
#include "../emulate.h"
#endif

#ifndef OPSTRUCTS_H
#define OPSTRUCTS_H

// required for C lexigraphical compilation
typedef void *PtrToBeCast;
// functions to apply shifting
typedef u32 (*Shifter)(u32*, u32, u32);
// typedef of execute function with dummy pointer arg
// will really take a BaseStruct address representing
// all the below types
typedef void (*Execute)(PtrToBeCast);

//////////////////////////////////////////////////////
// BASE //////////////////////////////////////////////
// Defines the two key components of every decoded
// instruction, the cond flag that is required to be
// checked on execution and the function to call on
// execution, which will take the address of the struct
// itself, fixing the base pointer from where it can
// fetch it's arguments
#define BASE         \
  u8 cond;           \
  u32* cpsr;         \
  Execute function;  

//////////////////////////////////////////////////////
// SHIFTING ARGS /////////////////////////////////////
// Inherits from base, contains standard cond flag and
// address of function to be executed by the emulator
// along with function specific pointers to registers,
// memory allocation for operand literals and a shifter
#define SHIFTING_ARGS \
  u32* op1;           \
  u32* op2;           \
  u32* shift;         \
  u32 _op2;           \
  u32 _shift;         \
  Shifter exShift;    \
  u32* des;

//////////////////////////////////////////////////////
// BASE STRUCT ///////////////////////////////////////
// type to represent the LARGEST of the below structs
// in memory, allowing for rapid memory access in a
// selection of calloced memory
typedef struct
{
  BASE
  char padding[64];
} BaseInstr;


typedef struct
{
  BASE
  u8 *halt;
} TerminateInstr;

//////////////////////////////////////////////////////
// SHIFTING INSTRUCTIONS /////////////////////////////
//////////////////////////////////////////////////////

// the basic shifting intruction that can be used
// for setting immediate values and the pre-execution
// shift
typedef struct   // for type checking only
{
  BASE
  SHIFTING_ARGS
} ShiftingInstr;

// DATA PROCESSING instructions require nothing more
// than that determined by the default base, hence
// repeated typedef for readability only
typedef struct   //  < BaseInstr
{
  BASE
  SHIFTING_ARGS
  u8 s;
} DataProcessingInstr;

// SINGLE DATA PROCESSING instructions also make use
// of the staple args and require immediate shifting
// to be set, along with specific p u and l flags
typedef struct   //  < BaseInstr
{
  BASE
  SHIFTING_ARGS
  u8 p; u8 u; u8 l;
  u8 *mem;
} SingleDataInstr;

//////////////////////////////////////////////////////
// MULTIPLY INSTRUCTION //////////////////////////////
//////////////////////////////////////////////////////

// TODO - Verify that multiply instruction
typedef struct    //  < BaseInstr
{
  BASE
  u32 *op1;
  u32 *op2;
  u32 *acc;
  u32 *des;
  u8     s;
} MultiplyInstr;

//////////////////////////////////////////////////////
// BRANCH INSTRUCTION ////////////////////////////////
//////////////////////////////////////////////////////

typedef struct    //  < BaseInstr
{
  BASE
  u32 *pc;
  u32 toAdd;
  u32 offset;   // to be signed on execution
} BranchInstr;

#endif
