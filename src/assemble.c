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
  // declare the temporary char array and li
  char line[MAX_CHAR_PER_LINE], *tmp;
  int noOfLines = linesInFile(file, line);
  // if file failed to open then return error
  if (file == NULL)
  {
    fprintf(stderr, "File error\n");
    exit(EXIT_FAILURE);
  }
  // initialise array of array of pointers to chars (ie, multiple strings)
  char*** lines = malloc(sizeof(char) * noOfLines);
  if (!lines)
  {
    fprintf(stderr, "Memory allocation error\n");
    exit(EXIT_FAILURE);
  }
  // for all the lines in the file
  for (int i = 0; fgets(line, MAX_CHAR_PER_LINE, file); i++)
  {
    // allocate the memory for the current line
    lines[i] = malloc(MAX_ARG_PER_LINE * sizeof(char));
    // apply strtok for the first time
    tmp = strtok(line, ", \n");
    // for all the potential arguments
    for (int j = 0; j < MAX_ARG_PER_LINE; j++)
    {
      // allocate memory for the copied string, say
      // 20 characters will be max length of args
      lines[i][j] = malloc(sizeof(char) * 20);
      // if tmp is not null, then copy the string
      if (tmp != NULL) strcpy(lines[i][j], tmp);
      // else just make null
      else lines[i][j] = NULL;
      // repeat the strtok
      tmp = strtok(NULL, ", \n");
    }
  }
  // close the file stream
  fclose(file);
  // return the array of string arrays
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
