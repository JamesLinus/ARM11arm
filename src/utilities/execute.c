///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: execute.c
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#include "execute.h"

void branch(PtrToBeCast base)
{
  BranchInstr *i = (BranchInstr *) base;
  if (checkFlags(i->cpsr, i->cond))
  {
    if (i->toAdd)
    {
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
    *(i->op2) = (*(i->exShift))(i->cpsr, *(i->op2), *(i->shift));

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
      setflags(i->cpsr, *(i->des));
    } 
  }
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
