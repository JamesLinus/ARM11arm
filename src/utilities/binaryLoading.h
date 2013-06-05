///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: binaryLoading.h
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#ifndef EMULATE_H
#include "../emulate.h"
#endif

#ifndef BIN_LOAD_H
#define BIN_LOAD_H

#include <stdio.h>
#include <stdlib.h>

FILE *openFile(char *path);
int fileExists(char *path);
long unsigned int getSize(FILE *file);
u32 *loadBinaryFile(char *path, u32 *memory);

#endif
