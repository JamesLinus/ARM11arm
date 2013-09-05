///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: ass_tokeniser.c
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#include "ass_private.h"
#include <string.h>

#define INSTR_MAX_ARGS 6 

char** tokeniseLine(char* line)
{
  char** tokens = calloc(1, INSTR_MAX_ARGS * sizeof(void*));
  uint32_t token = 0;
  tokens[token] = strtok(line, " ");

  while (token < INSTR_MAX_ARGS)
  {
    tokens[++token] = strtok(NULL, " ");
  }
  return tokens;
}

//TODO: make countLines better (maybe varibale)
char*** tokeniser(char* path)
{
  FILE* file = fopen(path, "rt");
  char*** output = calloc(1, countLines(file) * INSTR_MAX_ARGS * sizeof(void*));
  char** lines = readfile(file, countLines(file));
  uint32_t line = 0;

  while (line < countLines(file))// total number less than total lines
  {
    output[line] = tokeniseLine(lines[line]);
    line++;
  }
  fclose(file);
  return output;
}
