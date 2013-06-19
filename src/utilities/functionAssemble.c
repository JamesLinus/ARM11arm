///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: functionAssemble.c
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "functionAssemble.h"


const char *operands[] = {
  "and", "eor", "sub", "rsb", 
  "add", "adc", "sbc", "rsc", 
  "tst", "teq", "cmp", "cmn", 
  "orr", "mov", "bic", "mvn",
};

const int operandType[] = {
  COMPUTES,  COMPUTES,  COMPUTES,  COMPUTES,
  COMPUTES,  COMPUTES,  COMPUTES,  COMPUTES,
  SETS_CPSR, SETS_CPSR, SETS_CPSR, SETS_CPSR,
  COMPUTES,  SINGLE_OP_ASSIGNS, 0, 0, // TODO- Support bic and mvn
};

const int setcond[] = {
  1, 1, 1, 1,
  1, 1, 1, 1,
  0, 0, 0, 1,
  1, 1, 1, 1,
};


// to think about ==== what to do about the labels

// Includes setting of the SET COND flag
static inline u32 cmdToOpcode(char* cmd, int* type)
{
  int res = 0;
  while (strcmp(operands[res++], cmd));
  *type = operandType[res];
  return OPCODE_SHIFT(res) || SET_SHIFT(setcond[res]);
}

// Give with 0x prefix for hexidecimal
static inline u32 immediateToInt(char* str)
{
  int l = 0; while (str[l++]);
  if (str[0] = '#') str++;
  return strtoul(str, NULL, 10 + ((l > 2) && (str[1] == 'x'))*6);
}

u32 processOp2(char* operand)
{
  u32 val = immediateToInt(operand);
  return val;  //? that it?
}

// Entry point for all data processing operations
u32 assembleDataProcessing(char **args)
{
  // form the initial code using the template and an AL cond
  u32 binaryCode  = COND_SHIFT(AL_FLAG) & DATA_TEMPLATE;
  // add in the opcode value
  int opType = 0;
  binaryCode     |= cmdToOpcode(args[0], &opType);
  switch(opType)
  {
    case COMPUTES: 
      processComplutes(&binaryCode, args[1], args[2], args[3]);
      break;
    case SINGLE_OP_ASSIGNS: 
      processSingleOp(&binaryCode, args[1], args[2]);
      break;
    case SETS_CPSR:
      processSetsCpsr(&binaryCode, args[1], args[2]);
      break;
  }
  return binaryCode;
}

u32 assembleMultiply(u32 args, char** strings)
{ /*
  u32 binaryCode;
  u32 rd, rn, rs, rm;

  rd = (immediateToInt(strings[1]++) << 16);
  rn = (immediateToInt(strings[2]++) << 12);
  rs = (immediateToInt(strings[3]++) << 8);
  rm = (immediateToInt(strings[4]++);

  // mul
  if(args == 4)
  {
    binaryCode = 0xE0000090u;
  } else // mla
  {
    binaryCode = 0xE0200090u;
  }

  return binaryCode | (rd | rn | rd | rm);
  */ return 0;
}

// executed regardless of cond as far as I can tell
u32 assembleDataTransfer(u32 args, char** strings) 
{


/*
  //the instruction is a ldr
  if(!strcmp(strings[0], "ldr"))
  {
  //the L bit will need to be set
  u32 lBitMask = 0x00100000;
  binaryCode |= lBitMask;
  }
  //otherwise the L bit will be left clear
  
  //for <address>

  if(strings[2][0] == '=')
  {
    //numeric constant
    u32 numericConst = (u32)immediateToInt(++strings[2]);
    if(numbericConst <= 0xFF)
    {
      //use mov instruction instead
      //binaryCode = equivalent mov instruction
    }
    else 
    {
      //store in 4 bytes at the end of the file and 
      //pass the address using PC as the base register
      //using pre-indexing address
    }
    
  }
  else if
  {
    //preindexing
    //get the correct string
    char *address = strings[2];
    //get rid of the first '['
    address++;
    char *madeString;
    int i = 0;
    char *current = address;

    // TODO: finish!!!
    while(current[0] != ']')
    { 
      if(current[0] != ',')
      {
        madeString[i] = current[0];
        current++;
        i++;
      }
      else 
      {
          
      }
 
    }
  }
  else 
  {
    //post indexing
   
  }
*/
  return 0;
}

u32 assembleBranch(u32 args, char** strings, u32 memAddr)
{
  u32 binaryCode= 0x0a000000u;
  int32_t offset = atoi(strings[1]) - memAddr;

  if(!strcmp(strings[0], "beq"))
  {
    binaryCode |= COND_SHIFT(0);
  } else if(!strcmp(strings[0], "bne"))
  {
    binaryCode |= COND_SHIFT(1);
  } else if(!strcmp(strings[0], "bge"))
  {
    binaryCode |= COND_SHIFT(10);
  } else if(!strcmp(strings[0], "blt"))
  {
    binaryCode |= COND_SHIFT(11);
  } else if(!strcmp(strings[0], "bgt"))
  {
    binaryCode |= COND_SHIFT(12);
  } else if(!strcmp(strings[0], "ble"))
  {
    binaryCode |= COND_SHIFT(13);
  } else
  {
    binaryCode |= COND_SHIFT(14);
  } 

  return (u32)(binaryCode | ((offset >> 2) & 0x00ffffff));
}

