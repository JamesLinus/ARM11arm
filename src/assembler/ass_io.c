///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: ass_io.c
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#include "ass_private.h"

#define MAX_LINES 512

char** readfile(FILE* file, uint32_t num_lines)
{
  uint32_t curr_line = 0;
  char** string_lines = calloc(num_lines, MAX_LINES);

  fseek(file, 0, SEEK_SET);
  for (; fgets(string_lines[curr_line], MAX_LINES, file) != NULL; curr_line++);

  return string_lines;
}
