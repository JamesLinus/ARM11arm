///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: assemble.h
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#ifndef ASSEMBLE
#define ASSEMBLE

#include "res/uints.h"
#include "res/definitions.h"

typedef struct {
  char*** lines;
  int noOfLines;
} Source;

Source* tokeniser(char* path);
u32 linesInFile(FILE* file, char* line);
int main(int argc, char **argv);

#endif
