///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: execute.c
// Group: 21
// Memebers: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#include "execute.h"

void branch(PtrToBeCast base)
{
  BranchInstr *i = (BranchInstr *) base;
  if (checkFlags(i->cpsr, i->cond))
  {
    if (i->toAdd)
    {
      // we want to increment the pc before decode/possible execute
      i->pc += i->offset;
    }
    else
    {
      i->pc -= i->offset;
    }
  }
}

void singleDataTransfer(PtrToBeCast base)
{
  SingleDataInstr *i = (SingleDataInstr *) base;

  if (checkFlags(i->cpsr, i->cond))
  {
    *(i->op2) = (*(i->exShift))(*(i->op2), *(i->shift));

    if (i->p)
    {
      if (i->u)
      {
        i->op1 += *(i->op2);
      }
      else
      {
        i->op1 -= *(i->op2);
      }
      if (i->l)
      {
        *(i->des) = *(i->op2);
      }
      else
      {
        *(i->op2) = *(i->des);
      }
    }
    else
    {
      if (i->l)
      {
        *(i->des) = *(i->op2);
      }
      else
      {
        *(i->op2) = *(i->des);
      }
      if (i->u)
      {
        i->op1 += *(i->op2);
      }
      else
      {
        i->op1 -= *(i->op2);
      }
    }
  }
}

void multiply(PtrToBeCast base)
{
  MultiplyInstr* i = (MultiplyInstr*) base;

  if (checkFlags(i->cpsr, i->cond))
  {
    *(i->des) = ((*(i->op1)) * (*(i->op2))) + (*(i->acc));
    if(i->s)
    {
      setflags(i->cpsr, *(i->des), 0);
    } 
  }
}

// inefficent a lot of repetition will find a better solution later
void and(PtrToBeCast base)
{
  DataProcessingInstr* i = (DataProcessingInstr*) base;
  if (checkFlags(i->cpsr, i->cond))
  {
    *(i->op2) = (*(i->exShift))(*(i->op2), *(i->shift));
    *(i->des) = (*(i->op1)) & (*(i->op2)); 
    if(i->s)
    {
      setflags(i->cpsr, *(i->des), 0);
    } 
  } 
}
void eor(PtrToBeCast base)
{
  DataProcessingInstr* i = (DataProcessingInstr*) base;
  if (checkFlags(i->cpsr, i->cond))
  {
    *(i->op2) = (*(i->exShift))(*(i->op2), *(i->shift));
    *(i->des) = (*(i->op1)) ^ (*(i->op2)); 
    if(i->s)
    {
      setflags(i->cpsr, *(i->des), 0);
    } 
  }
}
void sub(PtrToBeCast base)
{
  DataProcessingInstr* i = (DataProcessingInstr*) base;
  if (checkFlags(i->cpsr, i->cond))
  {
    *(i->op2) = (*(i->exShift))(*(i->op2), *(i->shift));
    *(i->des) = (*(i->op1)) - (*(i->op2)); 
    if(i->s)
    {
      setflags(i->cpsr, *(i->des), 0);
    } 
  }
}
void rsb(PtrToBeCast base)
{
  DataProcessingInstr* i = (DataProcessingInstr*) base;
  if (checkFlags(i->cpsr, i->cond))
  {
    *(i->op2) = (*(i->exShift))(*(i->op2), *(i->shift));
    *(i->des) = (*(i->op2)) - (*(i->op1)); 
    if(i->s)
    {
      setflags(i->cpsr, *(i->des), 0);
    } 
  }
}
void add(PtrToBeCast base)
{
  DataProcessingInstr* i = (DataProcessingInstr*) base;
  if (checkFlags(i->cpsr, i->cond))
  {
    *(i->op2) = (*(i->exShift))(*(i->op2), *(i->shift));
    *(i->des) = (*(i->op1)) + (*(i->op2)); 
    if(i->s)
    {
      setflags(i->cpsr, *(i->des), 0);
    } 
  }
}
void tst(PtrToBeCast base)
{
  DataProcessingInstr* i = (DataProcessingInstr*) base;
  if (checkFlags(i->cpsr, i->cond))
  {
    *(i->op2) = (*(i->exShift))(*(i->op2), *(i->shift));
    if(i->s)
    {
      setflags(i->cpsr, (*(i->op1)) & (*(i->op2)), 0);
    } 
  }
}
void teq(PtrToBeCast base)
{
  DataProcessingInstr* i = (DataProcessingInstr*) base;
  if (checkFlags(i->cpsr, i->cond))
  {
    *(i->op2) = (*(i->exShift))(*(i->op2), *(i->shift));
    if(i->s)
    {
      setflags(i->cpsr, (*(i->op1)) ^ (*(i->op2)), 0);
    } 
  }
}
void cmp(PtrToBeCast base)
{
  DataProcessingInstr* i = (DataProcessingInstr*) base;
  if (checkFlags(i->cpsr, i->cond))
  {
    *(i->op2) = (*(i->exShift))(*(i->op2), *(i->shift));
    if(i->s)
    {
      setflags(i->cpsr, (*(i->op1)) - (*(i->op2)), 0);
    } 
  }
}
void orr(PtrToBeCast base)
{
  DataProcessingInstr* i = (DataProcessingInstr*) base;
  if (checkFlags(i->cpsr, i->cond))
  {
    *(i->op2) = (*(i->exShift))(*(i->op2), *(i->shift));
    *(i->des) = (*(i->op1)) | (*(i->op2)); 
    if(i->s)
    {
      setflags(i->cpsr, *(i->des), 0);
    } 
  }
}
void mov(PtrToBeCast base)
{
  DataProcessingInstr* i = (DataProcessingInstr*) base;
  if (checkFlags(i->cpsr, i->cond))
  {
    *(i->op2) = (*(i->exShift))(*(i->op2), *(i->shift));
    *(i->des) = (*(i->op2)); 
    if(i->s)
    {
      setflags(i->cpsr, *(i->des), 0);
    } 
  }
}

void setflags(u32* cpsr, u32 result, u8 carryOut)
{
  if(carryOut != 0)
  {

  }
  if(result == 0)
  {

  }

}