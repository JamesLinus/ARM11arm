///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: ass_data_processing.c
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#include "ass_private.h"

static uint32_t operand_2(char** op_2);
static uint32_t expression(char* op_2);
static uint32_t registor(char** op_2);

uint32_t ass_data_processing(char** line)
{
  uint32_t instr = 0xE0000000;
  char* set_CPRS [3] = {"tst", "teq", "cmp"};

  if(strcmp(line[0], "mov") == 0)
  {
    instr |= (0xE0900000 | operand_2(&line[2]) | REG_D(regToInt(line[1])));
  }
  else if(arrayContains(line[0], set_CPRS, 3))
    // make arrays contains return num so dont have to use strcmp below
  {
    instr |= (operand_2(&line[2]) | REG_N(regToInt(line[1])));

    if (strcmp(line[0], "tst") == 0)
    {
      instr |= 0x0110000;
    }
    else if(strcmp(line[0], "teq") == 0)
    {
      instr |= 0x01300000;
    }
    else
    {
      instr |= 0x01500000;
    }
  }
  else
  {
    instr |= (operand_2(&line[3]) | REG_N(regToInt(line[2])) 
          | REG_D(regToInt(line[1])));

    if (strcmp(line[0], "and") == 0)
    {
      return instr;
    }
    else if(strcmp(line[0], "eor") == 0)
    {
      instr |= 0x00200000;
    }
    else if(strcmp(line[0], "sub") == 0)
    {
      instr |= 0x00400000;
    }
    else if(strcmp(line[0], "rsb") == 0)
    {
      instr |= 0x00600000;
    }
    else if(strcmp(line[0], "add") == 0)
    {
      instr |= 0x00800000;
    }
    else
    {
      instr |= 0x01800000;
    }
  }
  return instr;
}

///////////////////////////////////////////////////////////////////////////////
// Helper Methods
///////////////////////////////////////////////////////////////////////////////

static inline uint32_t operand_2(char** op_2)
{
  if(op_2[0][0] == '#')
  {
    return expression(&op_2[0][1]);
  }
  return registor(op_2);
}

static uint32_t expression(char* op_2)
{
  uint32_t instr_op_2 = toInt(op_2);
  if(instr_op_2 > 255)
  {
    //TODO: Dont exit deal with it differently
    printf("Opperand 2 too large to be an imemdiate");
    exit(EXIT_FAILURE);
  }
  else
  {
    return instr_op_2;
  }
}

static uint32_t registor(char** op_2)
{
  uint32_t instr_op_2 = 0x00000000;

  if(strcmp(op_2[0], "lsl") == 0)
  {
    
  }
  else if(strcmp(op_2[0], "ror"))
  {

  }
  else if(strcmp(op_2[0], "asr"))
  {

  }
  else
  {

  }
  return instr_op_2;
}
