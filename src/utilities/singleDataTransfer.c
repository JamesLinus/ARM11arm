///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: singleDataTransfer.c
// Group: 21
// Memebers: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

void singleDataTransfer(PtrToBeCast* base)
{
  SingleDataInstr* i = (SingleDataInstr*) base;
  *(i->op2) = (*(i->exShift))(*(i->op2), *(i->shift));

  if(i->p)
  {
    if(i->u)
    {
      i->op1 += *(i->op2);
    } else
    {
      i->op1 -= *(i->op2);
    }
    if(i->l)
    {
      *(i->des) = *(i->op2);
    } else
    {
      *(i->op2) = *(i->des);
    }
  } else
  {
    if(i->l)
    {
      *(i->des) = *(i->op2);
    } else
    {
      *(i->op2) = *(i->des);
    }
    if(i->u)
    {
      i->op1 += *(i->op2);
    } else
    {
      i->op1 -= *(i->op2);
    }
  }
}

