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

// Execute function
// Deals with bitwise and functions
void and(PtrToBeCast base)
{
  // make appropriate cast
  DataProcessingInstr* i = (DataProcessingInstr*) base;
  // calculate the value of op2 using the shifting function
  *(i->op2) = (*(i->exShift))(i->cpsr, *(i->op2), *(i->shift));
  // calculate final result using the above
  *(i->des) = (*(i->op1)) & (*(i->op2)); 
  // if required, set the flags
  if(i->s) setflags(i->cpsr, *(i->des));
}

// Execute function
// Deals with bitwise exclusive or
void eor(PtrToBeCast base)
{
  // make appropriate casting
  DataProcessingInstr* i = (DataProcessingInstr*) base;
  // make calculation for the appropriate shift
  *(i->op2) = (*(i->exShift))(i->cpsr, *(i->op2), *(i->shift));
  // save the result into the destination
  *(i->des) = (*(i->op1)) ^ (*(i->op2)); 
  // if required, set flags
  if(i->s) setflags(i->cpsr, *(i->des));
}

// Execute function
// Deals with subtraction a - b
void sub(PtrToBeCast base)
{
  // make appropriate casting
  DataProcessingInstr* i = (DataProcessingInstr*) base;
  // make shift
  *(i->op2) = (*(i->exShift))(i->cpsr, *(i->op2), *(i->shift));
  // save to des
  *(i->des) = (*(i->op1)) - (*(i->op2)); 
  // if required, set flags
  if(i->s) setflags(i->cpsr, *(i->des));
}

// Execute function
// Deals with subtraction b - a
void rsb(PtrToBeCast base)
{
  // make appropriate cast
  DataProcessingInstr* i = (DataProcessingInstr*) base;
  // make shift
  *(i->op2) = (*(i->exShift))(i->cpsr, *(i->op2), *(i->shift));
  // save into destination
  *(i->des) = (*(i->op2)) - (*(i->op1)); 
  // if required, set flags
  if(i->s) setflags(i->cpsr, *(i->des));
}

// Execute function
// Deals with addition
void add(PtrToBeCast base)
{
  // make appropriate cast
  DataProcessingInstr* i = (DataProcessingInstr*) base;
  // make shift
  *(i->op2) = (*(i->exShift))(i->cpsr, *(i->op2), *(i->shift));
  // save into destination
  *(i->des) = (*(i->op1)) + (*(i->op2)); 
  // if required, set flags
  if(i->s) setflags(i->cpsr, *(i->des));
}

// Execute function
// Deals with AND but without writing to destination
void tst(PtrToBeCast base)
{
  // make appropriate cast
  DataProcessingInstr* i = (DataProcessingInstr*) base;
  // make shift for op2
  *(i->op2) = (*(i->exShift))(i->cpsr, *(i->op2), *(i->shift));
  // if required, set flags (sort of redundant, right?)
  if(i->s) setflags(i->cpsr, (*(i->op1)) & (*(i->op2)));
}

// Execute function
// Deals with EOR but without writing to destination
void teq(PtrToBeCast base)
{
  // make appropriate cast
  DataProcessingInstr* i = (DataProcessingInstr*) base;
  // make appropriate shift
  *(i->op2) = (*(i->exShift))(i->cpsr, *(i->op2), *(i->shift));
  // once again, flags
  if(i->s) setflags(i->cpsr, (*(i->op1)) ^ (*(i->op2)));
}

// Execute function
// Basically the subtraction, without writing to des
void cmp(PtrToBeCast base)
{
  // make appropriate cast
  DataProcessingInstr* i = (DataProcessingInstr*) base;
  // make shift
  *(i->op2) = (*(i->exShift))(i->cpsr, *(i->op2), *(i->shift));
  // set flags
  if(i->s) setflags(i->cpsr, (*(i->op1)) - (*(i->op2)));
}

// Execute function
// Handles bitwise ORing
void orr(PtrToBeCast base)
{
  // make appropriate cast
  DataProcessingInstr* i = (DataProcessingInstr*) base;
  // make the shift
  *(i->op2) = (*(i->exShift))(i->cpsr, *(i->op2), *(i->shift));
  // save into destination
  *(i->des) = (*(i->op1)) | (*(i->op2)); 
  // handle flags
  if(i->s) setflags(i->cpsr, *(i->des));
}

// Execute function
// Write to destination operand2
void mov(PtrToBeCast base)
{
  // make appropriate cast
  DataProcessingInstr* i = (DataProcessingInstr*) base;
  // make shift
  *(i->op2) = (*(i->exShift))(i->cpsr, *(i->op2), *(i->shift));
  // save to destination
  *(i->des) = (*(i->op2)); 
  // handle flags
  if(i->s) setflags(i->cpsr, *(i->des));
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
  *(i->des) = ((*(i->op1)) * (*(i->op2))) + (*(i->acc));
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
  *(i->op2) = (*(i->exShift))(i->cpsr, *(i->op2), *(i->shift));
  // generate unique code for each modifier
  // TODO - stop using separate vars for the p u & l
  int code = (i->p << 2) + (i->u << 1) + i->l;
  // switch for the op1 modifiers
  switch(code) {
    case 0x02u: case 0x03u:
    case 0x06u: case 0x07u: i->op1   += *(i->op2);
    case 0x04u: case 0x05u:
    case 0x00u: case 0x01u: i->op1   -= *(i->op2);
  } 
  // switch for the des modifiers
  switch(code) {
    case 0x01u: case 0x03u:
    case 0x05u: case 0x07u: *(i->des) = *(i->op2);
    case 0x00u: case 0x02u:
    case 0x04u: case 0x06u: *(i->op2) = *(i->des);
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
  // if the offset is to add
  if (i->toAdd)
  {
    // then increment the pc
    i->pc += i->offset;
    return;
  }
  // else decrement
  i->pc -= i->offset;
}

///////////////////////////////////////////////////////////////////////////////
// FLAG HANDLING
///////////////////////////////////////////////////////////////////////////////

void setflags(u32* cpsr, u32 result)
{
  // set the N flag
  *(cpsr) |= (result & N_MASK);
  // if the result indicates...
  if (!result)
  {
    // turn Z on
    *cpsr |= Z_MASK;
    return;
  }
  // else turn Z off
  *cpsr &= ~Z_MASK;
}

void setCflag(u32* cpsr, u32 carryOut)
{
  *cpsr &= ~C_MASK;	
  *cpsr |= (carryOut << 29);
}
