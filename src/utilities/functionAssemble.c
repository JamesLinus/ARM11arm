///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: functionAssemble.c
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#include "functionAssemble.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

enum DataProcessingType {COMPUTE, SINGLE_OPERAND, NO_COMPUTE};

//to think about ==== what to do about the labels

//helper function takes string argument, ditches the 'r' and returns 
//an integer value of the register, and shifts it a given amount to 
//be used as a mask

uint32_t strToInt(char* reg, uint32_t shift)
{
  return (uint32_t)atoi(++reg) << shift;  
}

uint32_t assembleDataProcessing(uint32_t arguments, char **strings)
{

  assert (arguments >=2 && arguments <=4);

  uint32_t binaryCode = 0;
  //cond is always 1110 
  uint32_t dataProcessingCond = 0xE0000000;
  //update to include condition
  binaryCode = dataProcessingCond;
  //next 2 bits are 0's no matter what
  uint32_t bits26and27mask = 0xF3FFFFFF;
  //update to include bits 26 and 27
  binaryCode = binaryCode | bits26and27mask;
  //TODO set bit 25 - the I bit
  //******************************
  
  //can use the mnemonic to determine type and layout of instruction
  //use an enum to distinguish
  
  enum DataProcessingType typeOfInstr;  

  //for bits 21 through 24 - opcode
  uint32_t opCodeMask;  

  if(!strcmp(strings[0], "and"))
  { 
     opCodeMask = 0xFE1FFFFFu;
     typeOfInstr = COMPUTE;
  }
  else if(!strcmp(strings[0], "eor"))
  { 
     opCodeMask = 0xFE3FFFFFu;
     typeOfInstr = COMPUTE;
  }
  else if(!strcmp(strings[0], "sub"))
  { 
     opCodeMask = 0xFE5FFFFFu;
     typeOfInstr = COMPUTE;
  }
  else if(!strcmp(strings[0], "rsb"))
  { 
     opCodeMask = 0xFE7FFFFFu;
     typeOfInstr = COMPUTE;
  }
  else if(!strcmp(strings[0], "add"))
  { 
     opCodeMask = 0xFE9FFFFFu;
     typeOfInstr = COMPUTE;
  }
  else if(!strcmp(strings[0], "orr"))
  { 
     opCodeMask = 0xFF9FFFFFu;
     typeOfInstr = COMPUTE;
  }  
  else if(!strcmp(strings[0], "mov"))
  { 
     opCodeMask = 0xFFBFFFFFu;
     typeOfInstr = SINGLE_OPERAND;
  } 
  else if(!strcmp(strings[0], "tst"))
  { 
     opCodeMask = 0xFF1FFFFFu;
     typeOfInstr = NO_COMPUTE;
  }
  else if(!strcmp(strings[0], "teq"))
  { 
     opCodeMask = 0xFF3FFFFFu;
     typeOfInstr = NO_COMPUTE;
  }
  else
  { 
     opCodeMask = 0xFF5FFFFFu;
     typeOfInstr = NO_COMPUTE;
  }
  //now we have the correct opCodeMask we can fill in those bits in the 
  //binaryCode
  binaryCode = binaryCode & opCodeMask;

  //for setting bit 20 - the S bit
  uint32_t SBitMask = 1 << 19;
  if(typeOfInstr == NO_COMPUTE)
  {
    binaryCode = binaryCode | SBitMask;
  }
  //otherwise leave the S bit as 0
  
  //now comes the hard bit
  char *reg = strings[1];

  //the first operand is ALWAYS a register   so:
  uint32_t regNo = strToInt(reg, 16);
  //setting first operand
  binaryCode = binaryCode | regNo;
  switch(typeOfInstr)
  {
  case COMPUTE:
    
    break;
  case SINGLE_OPERAND:
    break;
  case NO_COMPUTE:
    break;
  }

  return binaryCode;
}

// use (uint32_t)strtol() for hex values passed
uint32_t assembleMultiply(int arguments, char **strings)
{ 
  uint32_t binaryCode;
  uint32_t rd, rn, rs, rm;

  rd = strToInt(strings[1], 16);
  rn = strToInt(strings[2], 12);
  rs = strToInt(strings[3], 8);
  rm = strToInt(strings[4], 0);

  // mul
  if(arguments == 4)
  {
    binaryCode = 0xE0000090u;
  } else // mla
  {
    binaryCode = 0xE0200090u;
  }

  return binaryCode | (rd | rn | rd | rm);
}