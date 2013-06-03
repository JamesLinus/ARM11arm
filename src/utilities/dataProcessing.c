// PRE - Required that cond field is satisfied
//     - Required that BaseOpInstr is actually
//       data instruction struct
void dataProcessing(Arm* raspi, BaseOpInstr* b)
{
  // cast to the data instr type
  DataInstr* i = (DataInstr*) b;
  // declare the destination and input
  u32 *des = 0; u32 op2; u32* rn = i->rn;
  if (i->immd)  // if immediate is set
  {
    // get immediate part of operand
    u32 imm  = i->operand2 & OP_IMMD;
    // get value to rotate right by
    u8  val  = i->operand2 & OP_ROTATE >> 8u;
    // generate operand by rotate right
    op2      = ROR(imm, 1 << val);
  }
  else  // operand 2 is a register
  {
    u8   shift     = i->operand2 & OP_SHIFT >> 4u;
    u8   shiftType = shift & OP_SHIFT_TYPE >> 1u;
    u32* rm        = &(raspi->r[i->operand2 & RM_MASK]);
    u8   shiftSize = 0;
    if (shift & 0x01u) // if bit 4 is 1
    {
      // then shift by value in register
      u32* shiftReg = &(raspi->r[shift & 0x0fu >> 4]);
      shiftSize = *shiftReg & 0xffu;
    }
    else  // shift by a constant
    {
      shiftSize = shift & 0xff0u;
    }
    switch (shiftType)
    {
      // lsl
      case 0x0u: op2 = LSL(*rm,shiftSize); break;
      // lsr
      case 0x1u: op2 = LSR(*rm,shiftSize); break;
      // asr
      case 0x2u: op2 = ASR(*rm,shiftSize); break;
      // ror
      case 0x3u: op2 = ROR(*rm,shiftSize); break;
    }
  }
  switch (i->opcode)
  {
    case AND: *(i->rd) = *rn & op2; break;
    case EOR: *(i->rd) = *rn ^ op2; break;
    case SUB: *(i->rd) = *rn - op2; break;
    case RSB: *(i->rd) = op2 - *rn; break;
    case ADD: *(i->rd) = *rn + op2; break;
    // case ADC: case SBC: case RSC:
    case TST: *rn & op2; break;
    case TEQ: *rn ^ op2; break;
    case CMP: *rn - op2; break;
    // case CMN:
    case ORR: *(i->rd) = *rn | op2; break;
    case MOV: *(i->rd) = op2; break;
    // case BIC: case MVN:
  }
}
