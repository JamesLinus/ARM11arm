///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: branch.c
// Group: 21
// Memebers: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

void branch(PtrToBeCast* base)
{
  BranchInstr* i = (BranchInstr*) base;
  if(i->toAdd)
  {
    // we want to increment the pc before decode/possible execute
    i->pc += i->offset;
  } else
  {
    i->pc -= i->offset;
  }
}