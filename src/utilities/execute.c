///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: execute.c
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#include "execute.h"
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////
// DATA PROCESSING INSTRUCTIONS
///////////////////////////////////////////////////////////////////////////////

// macros for applying the functions, allows for
// DRYer function bodies
#define  APPLY(i, op) (*(i->op1)) op (*(i->op2))
#define _APPLY(i, op) (*(i->op2)) op (*(i->op1))

// Stage 1 of any data processing instruction, cast the given
// pointer and calculate the required shift. Return the pointer
// for further use (though of course as inline, not quite that)
static inline DataProcessingInstr* castAndShift(PtrToBeCast base)
{
  // make cast to the data processing struct
  DataProcessingInstr* i = (DataProcessingInstr*) base;
  // calculate the value of op2 using the shifting function
  *(i->op2) = (*(i->exShift))(i->cpsr, *(i->op2), *(i->shift), i->s);
  // return the casted and shift calculated struct
  return i;
}

// Stage 2 of most data processing, save the result into rd
// and then handle the flag setting
static inline void saveAndSet(DataProcessingInstr* i, u32 res)
{
  // calculate final result using the above
  *(i->des) = res; 
  // if required, set the flags
  if (i->s) setflags(i->cpsr, *(i->des));
}

// Execute function                                        !! AND !!
// Deals with bitwise and functions
void and(PtrToBeCast base)
{
  // deal with the casting and shift calculation
  DataProcessingInstr* i = castAndShift(base);
  // calc final, save and set flags if appropriate
  saveAndSet(i, APPLY(i, &));
}

// Execute function                                        !! EOR !!
// Deals with bitwise exclusive or
void eor(PtrToBeCast base)
{
  // deal with the casting and shift calculation
  DataProcessingInstr* i = castAndShift(base);
  // calc final, save and set flags if appropriate
  saveAndSet(i, APPLY(i, ^));
}

// Execute function                                        !! SUB !!
// Deals with subtraction a - b
void sub(PtrToBeCast base)
{
  // deal with the casting and shift calculation
  DataProcessingInstr* i = castAndShift(base);
  // calc final, save and set flags if appropriate
  saveAndSet(i, APPLY(i, -));
}

// Execute function                                        !! RSB !!
// Deals with subtraction b - a
void rsb(PtrToBeCast base)
{
  // deal with the casting and shift calculation
  DataProcessingInstr* i = castAndShift(base);
  // calc final, save and set flags if appropriate
  saveAndSet(i, _APPLY(i, -));
}

// Execute function                                        !! ADD !!
// Deals with addition
void add(PtrToBeCast base)
{
  // deal with the casting and shift calculation
  DataProcessingInstr* i = castAndShift(base);
  // calc final, save and set flags if appropriate
  saveAndSet(i, APPLY(i, +));
}

// Execute function                                        !! TST !!
// Deals with AND but without writing to destination
void tst(PtrToBeCast base)
{
  // deal with the casting and shift calculation
  DataProcessingInstr* i = castAndShift(base);
  // if required, set flags (sort of redundant, right?)
  if(i->s) setflags(i->cpsr, APPLY(i, &));
}

// Execute function                                        !! TEQ !!
// Deals with EOR but without writing to destination
void teq(PtrToBeCast base)
{
  // deal with the casting and shift calculation
  DataProcessingInstr* i = castAndShift(base);
  // once again, flags
  if(i->s) setflags(i->cpsr, APPLY(i, ^));
}

// Execute function                                        !! CMP !!
// Basically the subtraction, without writing to des
void cmp(PtrToBeCast base)
{
  // deal with the casting and shift calculation
  DataProcessingInstr* i = castAndShift(base);
  // set flags
  if(i->s) setflags(i->cpsr, APPLY(i, -));
}

// Execute function                                        !! ORR !!
// Handles bitwise ORing
void orr(PtrToBeCast base)
{
  // deal with the casting and shift calculation
  DataProcessingInstr* i = castAndShift(base);
  // calc final, save and set flags if appropriate
  saveAndSet(i, APPLY(i, |));
}

// Execute function                                        !! MOV !!
// Write to destination operand2
void mov(PtrToBeCast base)
{
  // deal with the casting and shift calculation
  DataProcessingInstr* i = castAndShift(base);
  // calc final, save and set flags if appropriate
  saveAndSet(i, *(i->op2));
}

///////////////////////////////////////////////////////////////////////////////
// MULTIPLY FUNCTION
///////////////////////////////////////////////////////////////////////////////

// Execute function
// Deals with the multiplication, ideally with 2s complement
void multiply(PtrToBeCast base)
{
  // cast to appropriate struct type
  MultiplyInstr* i = (MultiplyInstr*) base;
  // make calculation, move into destination
  *(i->des) = APPLY(i, *) + (*(i->acc));
  // if required, mark the flags
  if (i->s) setflags(i->cpsr, *(i->des));
}

///////////////////////////////////////////////////////////////////////////////
// SINGLE DATA TRANSFER
///////////////////////////////////////////////////////////////////////////////

// Execute function
// Deals with single data transfer
void singleDataTransfer(PtrToBeCast base)
{
  // make the appropriate casting
  SingleDataInstr *i = (SingleDataInstr *) base;
  // find the op2 value from appropriate shifting
  u32 offset = (*(i->exShift))(i->cpsr, *(i->op2), *(i->shift), 0);
  u32 basePtr = *i->op1;
  // generate unique code for each modifier
  // TODO - stop using separate vars for the p u & l
  int code = i->pul;
  int post = 0;
  // switch for the op1 modifiers
  switch(code) {
    //     Pre and Up
    case 0x06u: case 0x07u: basePtr += offset;  // for  U
    //     Pre and Down
    case 0x04u: case 0x05u: basePtr -= offset;  // for ~U
    //     Post and Up
    case 0x00u: case 0x01u: post =  offset;
    //     Post and Down
    case 0x02u: case 0x03u: post = -offset;
  } 
  if (i->pc) basePtr += 2;
  if (basePtr < MEMSIZE)
  {
    // switch for the des modifiers
    switch(code) {
      //     Is Load
      case 0x01u: case 0x03u:
      case 0x05u: case 0x07u: *i->des = _memget(i->mem, basePtr);
      //     Is Store
      case 0x00u: case 0x02u:
      case 0x04u: case 0x06u: _memset(i->mem, basePtr, *i->des);  // for ~L
    }
  }
  else printf("Error: Out of bounds memory access at address 0x%08x\n", basePtr);
  switch(code) {
    //     Pre and Up
    case 0x06u: case 0x07u: *i->op1   += *i->op2;  // for  U
    //     Pre and Down
    case 0x04u: case 0x05u: *i->op1   -= *i->op2;  // for ~U
  } 
}

///////////////////////////////////////////////////////////////////////////////
// BRANCH FUNCTION
///////////////////////////////////////////////////////////////////////////////

// Execute function
// Offsets the PC for the raspi
void branch(PtrToBeCast base)
{
  // make the casting to correct struct
  BranchInstr *i = (BranchInstr *) base;
  u32 offset = i->offset;
  if (offset & (1 << 23)) 
    offset = -(~offset & 0x007FFFFFu) - 1;
  *(i->pc) += offset + 1;
}

void terminate(PtrToBeCast base)
{
  TerminateInstr *i = (TerminateInstr *) base;
  *(i->halt) = 0;
}

