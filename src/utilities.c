///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: utilities.c
// Group: 21
// Memebers: amv12, lmj112, skd212
//
// TODO - Move the 2^16 bits into a const
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

FILE* openFile(char* path)
{
  // open the file
  FILE *file = fopen(path, "rb");
  return file;
}

long unsigned int getSize(FILE* file)
{
  // use fseek to set relative pointer pos in file
  fseek(file, 0, SEEK_END);
  // get size from current relative position of the seek
  // inside the file
  long unsigned int size = ftell(file);
  // reset the offset to the beginning of the file
  fseek(file, 0, SEEK_SET);
  return size;
} 

uint32_t* loadBinaryFile(char* path)
{
  // declare variables
  // the binary file pointer
  FILE *arm_bin = 0;
  // the size of the binary file
  long unsigned int size = 0;
  // the pointer to the buffer
  uint32_t *buffer = 0;

  arm_bin = openFile(path);

  // if the file is null
  if (!arm_bin)
  {
    // output error to stdout
    fprintf(stderr, "Error opening file.\n");
    // exit with a failure
    exit(EXIT_FAILURE);
  }

  // get the file size
  size = getSize(arm_bin);
  // adjust to get it in word size and offset termination character
  size = 1 + (size >> 2);

  // assert no emulator memory overflow
  if (size > 65536)
  {
    // output error to stdout
    fprintf(stderr, "Emulator memory overflow\n");
    // exit with a failure
    exit(EXIT_FAILURE);
  }

  // allocate memory in heap for the file contents
  // where size is the size of the file
  buffer = malloc(size);

  // if buffer is null, has not been allocated correctly
  if (!buffer)
  {
    // memory error, typically game over
    fprintf(stderr, "Error allocating memory.\n");
    // exit with failure
    exit(EXIT_FAILURE);
  }
  // use fread to read to the buffer
  fread(buffer, size, size, arm_bin);
  // use fclose to end the feed from the file
  fclose(arm_bin);
  return buffer;
}

