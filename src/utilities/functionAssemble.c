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

#define BRANCH_COND(i) (uint32_t)(i << 28)
#define toInt(c, str) scanf(c, str)
#define MAX_CHAR_PER_LINE 512
#define MAX_ARG_PER_LINE 5

enum DataProcessingType {COMPUTE, SINGLE_OPERAND, NO_COMPUTE};

//to think about ==== what to do about the labels

//helper function takes string argument, ditches the 'r' and returns 
//an integer value of the register, and shifts it a given amount to 
//be used as a mask

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

  //helper method for checking if operand2 is an expression or a shifted
  //register
  int isExpression(char *operand2)
  {
    if(operand2[0] == '#')
    {
      return 1;
    }else
    {
      return 0;
    }
  }

  //helper method to check if the expression is in hex form
  int isHex(char *expression)
  {
    if(expression[0] == '0' && expression[1] == 'x')
    {
      return 1;
    }else
    {
      return 0;
    }
  }
  

  //declaring variables for use in switch
  uint32_t regNo1;
  uint32_t regNo2;

  //expression if COMPUTE
  if(typeOfInstr == COMPUTE)
  {
    char *operand2 = strings[3];
  }else  //expression if SINGLE_OPERAND or NO_COMPUTE
  {
    char *operand2 = strings[2];
  }

  switch(typeOfInstr)
  {
  case COMPUTE:
    //setting rn and rd bits
    regNo1 = strToInt(strings[1], 16);
    regNo2 = strToInt(strings[2], 12);
    binaryCode = binaryCode | regNo1;
    binaryCode = binaryCode | regNo2;  
    if(isExpression(operand2))
    {
      operand2++;
      if(isHex(operand2))
      {
        operand2 = operand2 + 2;
	// the rest is HEX
      }
      else
      {
        // the rest is decimal 
      }
    }
    else
    {
      // operand2 is a shifted register	    
    }
    break;
  case SINGLE_OPERAND:
    //setting rd bits
    //no need to set rn bits
    regNo1 = strToInt(strings[1], 12);
    binaryCode = binaryCode | regNo1;
    break;
  case NO_COMPUTE:
    //setting rn bits
    //no need to set rd bits
    regNo1 = strToInt(strings[1], 16);
    binaryCode = binaryCode | regNo1;
    break;
 }
   
  



  return binaryCode;
}

uint32_t assembleMultiply(uint32_t args, char** strings)
{ 
  uint32_t binaryCode;
  uint32_t rd, rn, rs, rm;

  rd = strToInt(strings[1], 16);
  rn = strToInt(strings[2], 12);
  rs = strToInt(strings[3], 8);
  rm = strToInt(strings[4], 0);

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
uint32_t assembleDataTransfer(uint32_t args, char** strings)
{


  return 0;
}

uint32_t assembleBranch(uint32_t args, char** strings, uint32_t memAddr)
{
  uint32_t binaryCode= 0x0a000000u;
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

  return (uint32_t)(binaryCode | ((offset >> 2) & 0x00ffffff));
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
  FILE file = fopen(path, "r");
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