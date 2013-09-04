///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: emu_io.c
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#include "emu_private.h"
#include <stdlib.h>

static long unsigned int getSize(FILE *file)
{
  // use fseek to set relative pointer pos in file
  fseek(file, 0, SEEK_END);
  // get size from current relative position of the seek
  // inside the file
  // TODO: Does ftell() return size relative to start?
  long unsigned int size = ftell(file);
  // reset the offset to the beginning of the file
  fseek(file, 0, SEEK_SET);
  return size;
}

u32 *loadBinaryFile(char *path, u32 *memory)
{
  // declare variables
  // the binary file pointer
  FILE *arm_bin = fopen(path, "rb");
  // the size of the binary file
  long unsigned int size = 0;

  // if the file is null
  if (!arm_bin)
  {
    // output error to stdout
    fprintf(stderr, "Error opening file.\n");
    // exit with a failure
    exit(EXIT_FAILURE);
  }

  // get the file size
  size = getSize(arm_bin) + 1;

  // assert no emulator memory overflow
  if (size > MEMSIZE)
  {
    // output error to stdout
    fprintf(stderr, "Emulator memory overflow\n");
    // exit with a failure
    exit(EXIT_FAILURE);
  }

  // if buffer is null, has not been allocated correctly
  if (!memory)
  {
    // memory error, typically game over
    fprintf(stderr, "Error allocating memory.\n");
    // exit with failure
    exit(EXIT_FAILURE);
  }
  // use fread to read to the buffer
  fread(memory, 1, size, arm_bin);
  // use fclose to end the feed from the file
  fclose(arm_bin);
  return memory;
}

// POST: file saved at path + EXIT_SUCCESS
u32 writeBinaryFile(u32* instr, u32 noOfInstr, char* path)
{
  FILE* file = fopen(path, "wb");
  if (fwrite(instr, 4, noOfInstr, file) < noOfInstr)
  {
    perror("writeBinaryFile() fgets failed");
    exit(EXIT_FAILURE);
  }
  fclose(file);
  return EXIT_SUCCESS;
}
