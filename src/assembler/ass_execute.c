///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: ass_execute.c
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#include "ass_private.h"

static node* createSymbolTable(char*** tokens, uint32_t num_lines);

uint32_t* assemble(char*** tokens, uint32_t num_lines)
{
  uint32_t i = 0;
  uint32_t* assembled_instrs = calloc(num_lines, 8);
  char* data_processing[12] =     {"add", "sub", "rsb", "and", "eor", 
                                   "orr", "mov", "tst", "teq", "cmp", 
                                   "lsl", "andeq"};
  char* multiply[2] =             {"mul", "mla"};
  char* single_data_transfer[2] = {"ldr", "str"};
  char* branch[7] =               {"beq", "bne", "bge", "blt", "bgt", 
                                   "ble", "b"};
  node* symbol_table = createSymbolTable(tokens, num_lines);

  for (; i < num_lines; i++)
  {
    if(arrayContains(tokens[i][0], data_processing, 12))
    {
      assembled_instrs[i] = ass_data_processing(tokens[i]);
    }
    else if(arrayContains(tokens[i][0], multiply, 2))
    {
      assembled_instrs[i] = ass_multiply(tokens[i]);
    }
    else if(arrayContains(tokens[i][0], single_data_transfer, 2))
    {
      assembled_instrs[i] = ass_single_data_transfer(tokens[i], symbol_table);
    }
    else if(arrayContains(tokens[i][0], branch, 7))
    {
      assembled_instrs[i] = ass_branch(tokens[i], symbol_table);
    }
    else
    {
      printf("Unknown command");
    }
  }
  return assembled_instrs;
}

///////////////////////////////////////////////////////////////////////////////
// Helper Methods
///////////////////////////////////////////////////////////////////////////////

static node* createSymbolTable(char*** tokens, uint32_t num_lines)
{
  node* symbol_table = makeRBT();
  char* token;
  uint32_t curr_line = 0;
  for(; curr_line < num_lines; curr_line++)
  {
    token = tokens[curr_line][0];
    //TODO: double check this if statment
    if(token[strlen(token) - 1] == ':')
    {
      insert(symbol_table, NULL, token, &token);
      tokens[curr_line][0] = tokens[curr_line][1];
    }
  }
  return symbol_table;
}
