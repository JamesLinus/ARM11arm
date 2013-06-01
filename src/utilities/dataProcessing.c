// OP CODE DIGEST
// 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// --Cond- 0 1 I P U 0 0 L --Rn---|--Rn--|--------Offset----------
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Cond: Condition field.
// I:  Immediate offset, if set to 1 then Offset is viewed as a
//     shifted register. If not set, then interpretted as direct
//     value.
// P:  Pre/Post indexing bit. If set, offset is summed with the base
//     register prior to the transfer, whereas if off then summed
//     once finished.
// U:  Enables or disables P on an on/off basis as you'd expect
// L:  Load or store, if on then the word is stored into memory,
//     else the word is retrieved from memory
// Rn: Base pointer for the function entry
// Rd: Source destination register for the passed word
// Offset has been covered in the above definitions.
void dataProcessing(u32 inst)
{
  // CPRS updates still need to be implemented
  // need to find a way of not using the nexted statements
  // set up easy access to registors
  typedef arm.register[(inst >> 16) & 0x000F] operand1;
  typedef arm.register[(((inst >> 16) & 0x000F) + 1) / 2] operand2;


  // case where I = 0
  if (inst & 0x02000000 == 0)
  {
    u32 operand2 = arm.register[inst & 0x0000000F];
    if (inst & 0x00000010)
    {
      switch ((inst >> 4) & 0x00000006)
      {
      case 0:
        operand2 = operand2 << ((inst >> 7) & 0x0000003F);
        break;
      case 2:
        operand2 = operand2 >> ((inst >> 7) & 0x0000003F);
        break;
      case 4:
        break;
      case 5:
        (operand2 >> ((inst >> 7) & 0x0000003F) |
         (operand2 << (32 - ((inst >> 7) & 0x0000003F));
          break;
      }
    }
  }
    else   // I = 1
  {
    //convert 8 bit to 32 bit and rotate right 2* the 4 bit value specified
    operand2 = ((inst & 0x000000FF) >> ((inst >> 8) & 0x0000000F) * 2)) |
    ((inst & 0x000000FF) << (32 - ((inst >> 8) & 0x0000000F) * 2));
  }
  // switch on opcodes
  switch ((inst >> 20) & 0x01e)
  {
    // rdest = and
  case 0:
    arm.register[(inst >> 12) & 0x0000F] = operand1 & operand2;
    break;
    // rdest = exclusive or
  case 2:
    arm.register[(inst >> 12) & 0x0000F] = operand1 ^ operand2;
    break;
    // sub rdes = opr1 - opr2
  case 4:
    arm.register[(inst >> 12) & 0x0000F] = operand1 - operand2;
    break;
    // rdest = opr2 - opr1
  case 6:
    arm.register[(inst >> 12) & 0x0000F] = operand2 - operand1;
    break;
    // rdest = opr1 + opr2
  case 8:
    arm.register[(inst >> 12) & 0x0000F] = operand1 + operand2;
    break;
    // opr1 & opr2
  case 16:
    operand1 &operand2;
    break;
    // opr1 xor opr2
  case 18:
    operand1 ^operand2;
    break;
    // opr1 - opr2
  case 20:
    operand1 - operand2;
    break;
    // rdest = opr1 | opr2
  case 24:
    arm.register[(inst >> 12) & 0x0000F] = operand1 | operand2;
    break;
    // rest = opr2
  case 26:
    arm.register[(inst >> 12) & 0x0000F] = operand2;
    break;
  }
}