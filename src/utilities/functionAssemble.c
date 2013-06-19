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

#define TO_INT(c, str, shift) (fscanf(c, str) << shift)

// to think about ==== what to do about the labels

// Includes setting of the SET COND flag
static inline u32 cmdToOpcode(char* cmd, int* type)
{
  int res = 0;
  while (strcmp(operands[res++]));
  *type = operandType[res];
  return OPCODE_SHIFT(res) || SET_SHIFT(setcond[res]);
}

// Give with 0x prefix for hexidecimal
static inline immediateToInt(char* str)
{
  int l = 0; while(str[l++]);
  if (str[0] = '#') str++;
  return strtoul(str, NULL, 10 + ((l > 2) && (str[1] == 'x'))*6);
}

u32 processOp2(char* operand)
{
  u32 val = immediateToInt(operand);
  return val;  //? that it?
}

// Entry point for all data processing operations
u32 assembleDataProcessing(u32 arguments, char **args)
{
  // assert the correct number of arguments (between 2 and 4)
  assert (arguments >= 2 && arguments <= 4);
  // form the initial code using the template and an AL cond
  u32 binaryCode  = COND_SHIFT(AL_FLAG) & DATA_TEMPLATE;
  // add in the opcode value
  int opType = 0;
  binaryCode     |= cmdToOpcode(args[0], &opType);
  switch(opType)
  {
    case COMPUTES: 
      processComputes(&binaryCode, args[1], args[2], args[3]);
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
{ 
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
}

// executed regardless of cond as far as I can tell
u32 assembleDataTransfer(u32 args, char** strings)
{


  //the instruction is a ldr
  if(!strcmp(strings[0], "ldr"))
  {
  //the L bit will need to be set
  u32 lBitMask = 0x00100000;
  binaryCode = binaryCode | lBitMask;
  
  }
  else
  //the instruction is a str
  { 
  //the L bit is left clear
  }

  //for <address>

  if(strings[2][0] == '=')
  {
    //numeric constant
    u32 numericConst = TO_INT("%i", ++strings[2], 0);
    if(numbericConst < 0xFF)
    {
      //use mov instruction instead
    }
    else 
    {
      //store in 4 bytes at the end of the file and 
      //pass the address using PC as the base register
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

  return 0;
}

u32 assembleBranch(u32 args, char** strings, u32 memAddr)
{
  u32 binaryCode= 0x0a000000u;
  int32_t offset = atoi(strings[1]) - memAddr;

  if(!strcmp(strings[0], "beq"))
  {
    binaryCode |= BRANCH_COND(0);
  } else if(!strcmp(strings[0], "bne"))
  {
    binaryCode |= BRANCH_COND(1);
  } else if(!strcmp(strings[0], "bge"))
  {
    binaryCode |= BRANCH_COND(10);
  } else if(!strcmp(strings[0], "blt"))
  {
    binaryCode |= BRANCH_COND(11);
  } else if(!strcmp(strings[0], "bgt"))
  {
    binaryCode |= BRANCH_COND(12);
  } else if(!strcmp(strings[0], "ble"))
  {
    binaryCode |= BRANCH_COND(13);
  } else
  {
    binaryCode |= BRANCH_COND(14);
  } 

  return (u32)(binaryCode | ((offset >> 2) & 0x00ffffff));
}

uint32_t linesInFile(FILE* file)
{
  uint32_t lines = 0;
  fseek(file, 0, SEEK_SET);

  for(; !feof(file); fseek(file, 1, SEEK_CUR))
  {
    if(fgetc(file) == atoi("\n"))
      lines++;
  }
  // ++ because there will possibly be one less "\n" than lines
  return ++lines;
}

void saveToken(char* value, char* lines)
{
  if(value != NULL)
  {
    lines = malloc(strlen(value) + 1);
    strcpy(lines, value);
  }
}

char*** tokeniser(char* path)
{ 
  FILE* file = fopen(path, "r");
  char*** lines = calloc(linesInFile(file) * MAX_ARG_PER_LINE, 1);
  char line[MAX_CHAR_PER_LINE];

  for(int i = 0; fgets(line, MAX_CHAR_PER_LINE, file); i++)
  {
    saveToken(strtok(line, " "), lines[i][0]);
    for(int j = 1; j < MAX_CHAR_PER_LINE; j++)
    {
      saveToken(strtok(NULL, " "), lines[i][j]);
    }
  }
  fclose(file);
  return lines;
}
