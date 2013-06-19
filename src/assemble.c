///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: assemble.c
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "assemble.h"
#include "utilities/functionAssemble.h"

char*** tokeniser(char* path)
{ 
  // open the assembly file in read only
  FILE *file = fopen(path, "r");
  if (file == NULL)
  {
    fprintf(stderr, "File error.");
    exit(EXIT_FAILURE);
  }
  char line[MAX_CHAR_PER_LINE], *tmp;
  int noOfLines = linesInFile(file, line);
  // initialise array of array of pointers to chars (ie, multiple strings)
  char*** lines = malloc(sizeof(char) * noOfLines);
  for (int i = 0; fgets(line, MAX_CHAR_PER_LINE, file); i++)
  {
    lines[i] = malloc(MAX_ARG_PER_LINE * sizeof(char));
    tmp = strtok(line, ", \n");
    for (int j = 0; j < MAX_ARG_PER_LINE; j++)
    {
      lines[i][j] = malloc(sizeof(char)* 50);
      if (tmp != NULL)
        strcpy(lines[i][j], tmp);
      else lines[i][j] = NULL;
      tmp = strtok(NULL, ", \n");
    }
  }
  fclose(file);
  return lines;
}


u32 linesInFile(FILE* file, char* line)
{
  int lines = 0;
  fseek(file, 0, SEEK_SET);
  while (fgets(line, sizeof line, file) != NULL) lines++;
  fseek(file, 0, SEEK_SET);
  return lines;
}

void saveToken(char* value, char* lines)
{
  if(value != NULL)
  {
    lines = malloc(strlen(value) + 1);
    strcpy(lines, value);
  }
}

int main(int argc, char **argv) {
  char *path; int suppress = 1; 
  switch (argc)
  {
    // case 0 for testing purposes
    case 0: path = (char *)argv; break;
    case 2: path = argv[1]; suppress = 0; break;
    default: 
      fprintf(stderr, "No FILE provided.\n"); 
      return NO_FILE_FOUND;
  }
  char*** lines = tokeniser(path);
  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < MAX_ARG_PER_LINE; j++)
      printf("%s,  ", lines[i][j]);
    printf("\n");
  }
  return EXIT_SUCCESS;
}
