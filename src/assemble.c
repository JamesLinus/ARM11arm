///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: assemble.c
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include "assemble.h"
#include "utilities/functionAssemble.h"

char*** tokeniser(char* path)
{ 
  // open the assembly file in read only
  FILE file = fopen(path, "r");
  // initialise array of array of pointers to chars (ie, multiple strings)
  char*** lines = calloc(linesInFile(file) * MAX_ARG_PER_LINE, 1);
  // initialise 
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


int main(int argc, char **argv) {
  return EXIT_SUCCESS;
}
