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
  BaseInstr* base = raspi->dm[index];
  // cond is the same no matter the instruction
  base.cond = instr >> 28;

  if (IS_DATA(instr))
  { // opcode matches data processing
    DataProcessingInstr* i = (DataProcessingInstr*) &base;
    i.opcode = instr & DATA_OP_MASK;
    switch(i.opcode)
    {
      case 0: i.function = 0; break; // add funciton pointer
      case 1: i.function = 0; break; // add funciton pointer
      case 2: i.function = 0; break; // add funciton pointer
      case 3: i.function = 0; break; // add funciton pointer
      case 4: i.function = 0; break; // add funciton pointer
      case 8: i.function = 0; break; // add funciton pointer
      case 9: i.function = 0; break; // add funciton pointer
      case 10: i.function = 0; break; // add funciton pointer
      case 12: i.function = 0; break; // add funciton pointer
      case 13: i.function = 0; break; // add funciton pointer
    }
    i.op1 = raspi.r[instr & RN_MASK];
    i.des = raspi.r[instr & RD_MASK];
    i.op2 = imediateOrReg(instr);

  }
  else if (IS_MUL(instr))
  { // opcode matches multiplication (not long)

  }
  else if (IS_S_DATA(instr))
  { // opcode matches single data transfer

  }
  /* else if (IS_BLOCK_DATA(instr))
  { // opcode matches block transfer
    
  } */
  else if (IS_BRANCH(instr))
  { // opcode matches a branch statement 

  }
  return (BaseOpInstr*) &(raspi->dm[index]);
}

u32* imediateOrReg(u32 instr)
{
  u32 opr2 = instr & DATA_OPR_2;
  if(instr & IMMEDIATE_MASK)
  {
    // only shifted 7 due to multiply by 2
    return &ROR((instr & DATA_OP2_ROTATE) >> 7, opr2 & DATA_OP2_IMM)
  } else
  {
    u32 shift;
    u32 opr2 = instr & RM_MASK;

    if(instr & DATA_OP2_CTRL)
    {
      // & has precedence so no brackets
      shift = raspi->r[instr & RS_MASK >> 8];
    } else
    {
      shift = instr & DATA_OP2_INT >> 7
    }
    switch(instr & DATA_OP2_SHIFT >> 5)
    {
      case 1: return opr2 << shift;
      case 2: return opr2 >> shift;
      case 3: return ASR(shift, opr2);
      case 4: return ROR(shift, opr2);
    }
  }
}










