// PRE - Required that cond field is satisfied
//     - Required that BaseOpInstr is actually
//       data instruction struct
void dataProcessing(Arm* raspi, BaseOpInstr* i)
{
  // cast to the data instr type
  DataInstr* i = (DataInstr*) i;
  // declare the destination and input
  u32 *des = 0; u32 *in = 0;
  if (i->immd)
  {
    u32 imm = i->operand & OP_IMMD
    u8 rot = i->operand & OP_ROTATE >> 8u

  }
}