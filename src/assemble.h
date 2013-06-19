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

char*** tokeniser(char* path);
u32 linesInFile(FILE* file, char* line);
void saveToken(char* value, char* lines);
int main(int argc, char **argv);

#endif