///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: execute.c
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#include "execute.h"
#include <stdio.h>

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

// inefficent a lot of repetition will find a better solution later
void and(PtrToBeCast base)
{
  DataProcessingInstr* i = (DataProcessingInstr*) base;
  if (checkFlags(i->cpsr, i->cond))
  {
    *(i->op2) = (*(i->exShift))(i->cpsr, *(i->op2), *(i->shift));
    *(i->des) = (*(i->op1)) & (*(i->op2)); 
    if(i->s)
    {
      setflags(i->cpsr, *(i->des));
    } 
  } 
}
void eor(PtrToBeCast base)
{
  DataProcessingInstr* i = (DataProcessingInstr*) base;
  if (checkFlags(i->cpsr, i->cond))
  {
    *(i->op2) = (*(i->exShift))(i->cpsr, *(i->op2), *(i->shift));
    *(i->des) = (*(i->op1)) ^ (*(i->op2)); 
    if(i->s)
    {
      setflags(i->cpsr, *(i->des));
    } 
  }
}
void sub(PtrToBeCast base)
{
  DataProcessingInstr* i = (DataProcessingInstr*) base;
  if (checkFlags(i->cpsr, i->cond))
  {
    *(i->op2) = (*(i->exShift))(i->cpsr, *(i->op2), *(i->shift));
    *(i->des) = (*(i->op1)) - (*(i->op2)); 
    if(i->s)
    {
      setflags(i->cpsr, *(i->des));
    } 
  }
}
void rsb(PtrToBeCast base)
{
  DataProcessingInstr* i = (DataProcessingInstr*) base;
  if (checkFlags(i->cpsr, i->cond))
  {
    *(i->op2) = (*(i->exShift))(i->cpsr, *(i->op2), *(i->shift));
    *(i->des) = (*(i->op2)) - (*(i->op1)); 
    if(i->s)
    {
      setflags(i->cpsr, *(i->des));
    } 
  }
}
void add(PtrToBeCast base)
{
  DataProcessingInstr* i = (DataProcessingInstr*) base;
  if (checkFlags(i->cpsr, i->cond))
  {
    *(i->op2) = (*(i->exShift))(i->cpsr, *(i->op2), *(i->shift));
    *(i->des) = (*(i->op1)) + (*(i->op2)); 
    if(i->s)
    {
      setflags(i->cpsr, *(i->des));
    } 
  }
}
void tst(PtrToBeCast base)
{
  DataProcessingInstr* i = (DataProcessingInstr*) base;
  if (checkFlags(i->cpsr, i->cond))
  {
    *(i->op2) = (*(i->exShift))(i->cpsr, *(i->op2), *(i->shift));
    if(i->s)
    {
      setflags(i->cpsr, (*(i->op1)) & (*(i->op2)));
    } 
  }
}
void teq(PtrToBeCast base)
{
  DataProcessingInstr* i = (DataProcessingInstr*) base;
  if (checkFlags(i->cpsr, i->cond))
  {
    *(i->op2) = (*(i->exShift))(i->cpsr, *(i->op2), *(i->shift));
    if(i->s)
    {
      setflags(i->cpsr, (*(i->op1)) ^ (*(i->op2)));
    } 
  }
}
void cmp(PtrToBeCast base)
{
  DataProcessingInstr* i = (DataProcessingInstr*) base;
  if (checkFlags(i->cpsr, i->cond))
  {
    *(i->op2) = (*(i->exShift))(i->cpsr, *(i->op2), *(i->shift));
    if(i->s)
    {
      setflags(i->cpsr, (*(i->op1)) - (*(i->op2)));
    } 
  }
}
void orr(PtrToBeCast base)
{
  DataProcessingInstr* i = (DataProcessingInstr*) base;
  if (checkFlags(i->cpsr, i->cond))
  {
    *(i->op2) = (*(i->exShift))(i->cpsr, *(i->op2), *(i->shift));
    *(i->des) = (*(i->op1)) | (*(i->op2)); 
    if(i->s)
    {
      setflags(i->cpsr, *(i->des));
    } 
  }
}
void mov(PtrToBeCast base)
{
  DataProcessingInstr* i = (DataProcessingInstr*) base;
  if (checkFlags(i->cpsr, i->cond))
  {
    *(i->op2) = (*(i->exShift))(i->cpsr, *(i->op2), *(i->shift));
    *(i->des) = (*(i->op2)); 
    if(i->s)
    {
      setflags(i->cpsr, *(i->des));
    } 
  }
}


void setflags(u32* cpsr, u32 result)
{
  if(result == 0)
  {
    *cpsr |= Z_MASK;
  } else
  {
    *cpsr &= ~Z_MASK;
  }
  //for setting N flag
  *(cpsr) |= (result & N_MASK);

}

void setCflag(u32* cpsr, u32 carryOut)
{
  *cpsr &= ~C_MASK;	
  *cpsr |= (carryOut << 29);
}
