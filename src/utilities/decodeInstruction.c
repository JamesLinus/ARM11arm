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