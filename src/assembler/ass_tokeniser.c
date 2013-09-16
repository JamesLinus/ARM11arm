///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: ass_tokeniser.c
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#include "ass_private.h"

#define OP_MAX_ARGS 6 

static char** tokeniseLine(char* string_line);
static uint32_t countLines(FILE* file);

char*** tokeniser(char* path)
{
  uint32_t curr_line = 0;
  FILE* file = fopen(path, "rt");
  uint32_t num_lines = countLines(file);
  char*** tokens = calloc(1, num_lines * OP_MAX_ARGS * sizeof(void*));
  char** string_lines = readfile(file, num_lines);
  fclose(file);

  for (; curr_line < num_lines; curr_line++)
  {
    tokens[curr_line] = tokeniseLine(string_lines[curr_line]);
  }
  return tokens;
}

///////////////////////////////////////////////////////////////////////////////
// Helper Methods
///////////////////////////////////////////////////////////////////////////////

static char** tokeniseLine(char* string_line)
{
  char** line = calloc(1, OP_MAX_ARGS * sizeof(void*));
  uint32_t token = 0;
  line[token] = strtok(string_line, " ");

  while (token < OP_MAX_ARGS)
  {
    line[++token] = strtok(NULL, " ");
  }
  return line;
}

static uint32_t countLines(FILE* file)
{
  uint32_t num_lines = 1;
  uint32_t num_chars = 0;
  int ch = 0;

  while ((ch = fgetc(file)) != EOF)
  {
    fseek(file, num_chars++, SEEK_SET);
    if((char)ch == '\n')
    {
      num_lines++;
    }
  }
  return num_lines;
}
