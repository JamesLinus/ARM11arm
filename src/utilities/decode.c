///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: decode.c
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#include "decode.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////
// THE DECODE FUNCTION - GROUND 0
///////////////////////////////////////////////////////////////////////////////

BaseInstr *decodeInstruction(Arm *raspi, u32 index)
{
  u32 instr = raspi->em[index];
  BaseInstr *base = &(raspi->dm[index]);
  // cond is the same no matter the instruction
  base->cond = instr >> 28;
  // set cpsr reg pointer, used in most
  base->cpsr = &(raspi->cpsr);
  //////////////////////////////////////////////////////////////////
  if (IS_DATA(instr))
  {
    // opcode matches data processing
    DataProcessingInstr *i = (DataProcessingInstr *) base;
    // isolate the opcode
    u8 opcode = (instr & DATA_OP_MASK) >> 21;
    // set pointer to op1 register
    i->op1    = &(raspi->r[(instr & RN_MASK) >> 16]);
    // set pointer to destination register
    i->des    = &(raspi->r[(instr & RD_MASK) >> 12]);
    i->s      = (instr >> 20) & 0x01u;
    // set the shift function and immediate settings
    setShifting(raspi, instr, (ShiftingInstr*) i);
    // start a switch on the opcode
    switch (opcode)
    { // use switch to set the function 
      case AND: i->function = &and; break;
      case EOR: i->function = &eor; break;
      case SUB: i->function = &sub; break;
      case RSB: i->function = &rsb; break;
      case ADD: i->function = &add; break;
      // case ADC: case SBC: case RSC:
      case TST: i->function = &tst; break;
      case TEQ: i->function = &teq; break;
      case CMP: i->function = &cmp; break;
      // case CMN:
      case ORR: i->function = &orr; break;
      case MOV: i->function = &mov; break;
      // case BIC: case MVN:
    }
  }
  //////////////////////////////////////////////////////////////////
  else if (IS_MUL(instr))
  {
    // opcode matches multiplication (not long)
    MultiplyInstr *i = (MultiplyInstr *) base;
    // get the op1 from the instruction
    i->op1 = &(raspi->r[instr & MUL_RM_MASK]);
    // retrive op2 similarly from instr
    i->op2 = &(raspi->r[(instr & MUL_RS_MASK) >> 8 ]);
    i->s   = (instr >> 20) & SET_FLAGS_S;
    if (instr & ACCUM_MASK)
    {
      i->acc = &(raspi->r[(instr & MUL_RN_MASK) >> 12]);
    }
    else { i->acc = 0; }
    // set the destination register
    i->des = &(raspi->r[(instr & MUL_RD_MASK) >> 16]);
    i->function = &multiply;
  }
  //////////////////////////////////////////////////////////////////
  else if (IS_S_DATA(instr))
  {
    // opcode matches single data transfer
    SingleDataInstr *i = (SingleDataInstr *) base;
    i->function = (Execute)&singleDataTransfer;
    // extract the p u and l flags
    i->p = (instr & P_INDEX_MASK) >> 23;
    i->u = (instr & S_DATA_UP) >> 22;
    i->l = (instr & LOAD_STORE_MASK) >> 19;
    i->op1 = &(raspi->r[(instr & RN_MASK) >> 16]);
    i->des = &(raspi->r[(instr & RD_MASK) >> 12]);
    // modify instruction for immediate idiosyncrasy
    instr ^= IMMEDIATE_MASK;
    // sorting out shifting
    setShifting(raspi, instr, (ShiftingInstr*) i);
    i->function = &singleDataTransfer;
  }
  //////////////////////////////////////////////////////////////////
  else if (IS_BRANCH(instr))
  {
    // opcode matches a branch statement
    BranchInstr *i = (BranchInstr *) base;
    i->function    = (Execute)&branch;
    i->toAdd       = instr & BRANCH_CTRL;
    i->offset      = (instr & BRANCH_OFFSET) << 2;
    i->pc          = &(raspi->pc);
  }
  return (BaseInstr *) & (raspi->dm[index]);
}

///////////////////////////////////////////////////////////////////////////////
// SHIFTING CALCULATIONS
///////////////////////////////////////////////////////////////////////////////

void setShifting(Arm *raspi, u32 instr, ShiftingInstr *i)
{
  // retrieve last twelve bits for operand
  u32 rawOperand = instr & DATA_OPR_2;
  // set default shift type
  u8   shiftType = 0x3u;
  if (instr & IMMEDIATE_MASK)  // if immediate is set
  {
    // get immediate part of operand
    u32 imm   = rawOperand & OP_IMMD;
    // get value to rotate right by
    u8  val   = (rawOperand & OP_ROTATE) >> 8u;
    // generate operand by rotate right
    i->_op2   = ROR(imm, (val << 1));
    // set the exposed pointer to internal literal
    i->op2    = &(i->_op2);
    // set shift value to 0
    i->_shift = 0u;
    // set exposed shift pointer to the internal literal
    i->shift  = &(i->_shift);
  }
  else  // operand 2 is a register
  {
    // isolate shift information
    u8 shift   = (rawOperand & OP_SHIFT) >> 4u;
    // reset the shifting type
    shiftType  = (shift & OP_SHIFT_TYPE) >> 1u;
    // assign pointer to the op2 as a raspi register
    i->op2     = &(raspi->r[rawOperand & RM_MASK]);
    // printf("Interested in THIS --- %d\n\n", rawOperand & RM_MASK);
    if (shift & 0x01u) // if bit 4 is 1
    {
      // then shift by value in register
      i->shift = &(raspi->r[(shift & 0x0fu) >> 4]);
    }
    else  // shift by a constant
    {
      // set literal value of shift
      i->_shift = shift & 0xf8u;
      // set pointer to internal literal
      i->shift  = &(i->_shift);
    }
  }
  switch (shiftType)
  {
    // lsl
    case 0x0u: i->exShift = &lsl; break;
    // lsr
    case 0x1u: i->exShift = &lsr; break;
    // asr
    case 0x2u: i->exShift = &asr; break;
    // ror
    case 0x3u: i->exShift = &ror; break;
  }
}


///////////////////////////////////////////////////////////////////////////////
// SHIFT FUNCTION WRAPPERS
///////////////////////////////////////////////////////////////////////////////

u32 lsl(u32* cpsr, u32 a, u32 b) 
{ 
  setCflag(cpsr, (a >> (32 - (b - 1))) & FIRST_BIT_MASK);
  return LSL(a,b); 
}

u32 lsr(u32* cpsr, u32 a, u32 b) 
{ 
  setCflag(cpsr, (a << (32 - (b - 1))) & FIRST_BIT_MASK);
  return LSR(a,b); 
}

u32 asr(u32* cpsr, u32 a, u32 b) 
{ 
  setCflag(cpsr, (a << (32 - (b - 1))) & FIRST_BIT_MASK);
  return ASR(a,b); 
}

u32 ror(u32* cpsr, u32 a, u32 b) 
{ 
  setCflag(cpsr, (a << (32 - (b - 1))) & FIRST_BIT_MASK);
  return ROR(a,b); 
}

///////////////////////////////////////////////////////////////////////////////
// TESTING ONLY - TO BE REMOVED
///////////////////////////////////////////////////////////////////////////////

void setmem(Arm *raspi, char* binStr, int i)
{
  raspi->em[1] = atoi(binStr);
  for (int j = 0; j < 32; j++)
  {
    raspi->em[1] <<= 1;
    raspi->em[1] += (binStr[j] == '1');
  } 
}

void runFunction(BaseInstr *i)
{
  //return void;
  ShiftingInstr *instr = (ShiftingInstr*) i;
  instr->function(instr);
}
