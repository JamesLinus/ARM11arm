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
#include "utilities/bstMap.h"
#include "utilities/functionAssemble.h"

Source* initSource(int noOfLines)
{
  Source *src = calloc(sizeof(Source), 1);
  src->noOfLines = noOfLines;
  src->lines = calloc(noOfLines * sizeof(char*), 1);
  for (int i = 0; i < noOfLines; i++)
    src->lines[i] = malloc(MAX_ARG_PER_LINE * sizeof(char*));
  if (!src->lines)
  {
    fprintf(stderr, "Memory allocation error\n");
    exit(EXIT_FAILURE);
  }
  return src;
}

Source* tokeniser(char* path)
{ 
  // open the assembly file in read only
  FILE *file = fopen(path, "r");
  // declare the temporary char array and li
  char line[MAX_CHAR_PER_LINE], *tmp;
  Source* src = initSource(linesInFile(file, line));
  // if file failed to open then return error
  if (file == NULL)
  {
    fprintf(stderr, "File error\n");
    exit(EXIT_FAILURE);
  }
  // for all the lines in the file
  for (int i = 0; i < src->noOfLines; i++)
  {
    fgets(line, MAX_CHAR_PER_LINE, file);
    // apply strtok for the first time
    tmp = strtok(line, ", \n");
    // for all the potential arguments
    for (int j = 0; j < MAX_ARG_PER_LINE; j++)
    {
      // allocate memory for the copied string, say
      // 20 characters will be max length of args
      src->lines[i][j] = malloc(sizeof(char) * 200);
      // if tmp is not null, then copy the string
      if (tmp != NULL) strcpy(src->lines[i][j], tmp );
      // else just make null
      else src->lines[i][j] = NULL;
      // repeat the strtok
      tmp = strtok(NULL, ", \n");
    }
  }
  // close the file stream
  fclose(file);
  // return the array of string arrays
  return src;
}

u32 linesInFile(FILE* file, char* line)
{
  int lines = 0;
  fseek(file, 0, SEEK_SET);
  while (fgets(line, MAX_CHAR_PER_LINE, file) != NULL) lines++;
  fseek(file, 0, SEEK_SET);
  return lines;
}

void assemble(Source *src)
{
  // first pass to generate tree
  tree_entry *symbolTree = createTree();
  for (int i = 0; i < src->noOfLines; i++)
    if (IS_SYMBOL(src->lines[i][0]))
      insert(&symbolTree, src->lines[i][0], (i << 2));
  // decode
    
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
  Source* src = tokeniser(path);
  assemble(src);
  return EXIT_SUCCESS;
}
