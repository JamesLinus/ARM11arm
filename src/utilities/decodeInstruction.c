///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: decodeInstruction.c
// Group: 21
// Memebers: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

BaseOpInstr* decodeInstruction(Arm* raspi, u32 index)
{
  u32 instr = raspi->em[index];
  if (IS_DATA(instr))
  { // opcode matches data processing
    DataInstr* i = (DataInstr*) &(raspi->dm[index]);
    i->jump     = J_DATA;
    i->cond     = instr >> 28;
    i->immd     = instr & IMMEDIATE_MASK >> 25;
    i->opcode   = instr & DATA_OP_MASK >> 21;
    i->setcond  = instr & SET_COND_MASK >> 20;
    i->rn       = &(raspi->r[instr & RN_MASK >> 16]);
    i->rd       = &(raspi->r[instr & RD_MASK >> 12]);
    i->operand2 = instr & DATA_OP_MASK;
  }
  else if (IS_MUL(instr))
  { // opcode matches multiplication (not long)
    MulInstr* i = (MulInstr*) &(raspi->dm[index]);
    i->jump     = J_MUL;
    i->cond     = instr >> 28;
    i->accum    = instr & ACCUM_MASK >> 21;
    i->setcond  = instr & SET_COND_MASK >> 20;
    // note that rn and rd are swapped for mul
    i->rd       = &(raspi->r[instr & RN_MASK >> 16]);
    i->rn       = &(raspi->r[instr & RD_MASK >> 12]);
    i->rs       = &(raspi->r[instr & RS_MASK >>  8]);
    i->rm       = &(raspi->r[instr & RM_MASK]);
  }
  else if (IS_S_DATA(instr))
  { // opcode matches single data transfer
    SingleDataInstr* i = (SingleDataInstr*) &(raspi->dm[index]);
    i->jump     = J_S_DATA;
    i->cond     = instr >> 28;
    i->immd     = instr & IMMEDIATE_MASK >> 25; 
    i->pindex   = instr & P_INDEX_MASK >> 24;
    i->up       = instr & S_DATA_UP >> 23;
    i->ls       = instr & LOAD_STORE_MASK >> 20;
    i->rn       = &(raspi->r[instr & RN_MASK >> 16]);
    i->rd       = &(raspi->r[instr & RD_MASK >> 12]);
    i->offset   = instr & S_DATA_OFFSET;
  }
  /* else if (IS_BLOCK_DATA(instr))
  { // opcode matches block transfer
    // TODO - Implement!
  } */
  else if (IS_BRANCH(instr))
  { // opcode matches a branch statement 
    BranchInstr* i = (BranchInstr*) &(raspi->dm[index]);
    i->jump     = J_BRANCH;
    i->cond     = instr >> 28;
    i->offset   = instr & BRANCH_OFFSET;
  }
  return (BaseOpInstr*) &(raspi->dm[index]);
}