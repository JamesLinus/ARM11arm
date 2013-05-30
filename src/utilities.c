///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: utilities.c
// Group: 21
// Memebers: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint32_t* loadBinaryFile(char* path)
{
  // declare variables
  // the binary file pointer
  FILE *arm_bin = 0;
  // the size of the binary file
  long unsigned int size = 0;
  // the pointer to the buffer
  uint32_t *buffer = 0;

  // open the file
  arm_bin = fopen(path, "rb");

  // if the file is null
  if (!arm_bin)
  {
    // output error to stdout
    fprintf(stderr, "Error opening file.\n");
    // exit with a failure
    exit(EXIT_FAILURE);
  }

  // use fseek to set relative pointer pos in file
  fseek(arm_bin, 0, SEEK_END);
  // get size from current relative position of the seek
  // inside the file
  size = ftell(arm_bin);
  // reset the offset to the beginning of the file
  fseek(arm_bin, 0, SEEK_SET);

  // allocate memory in heap for the file contents
  // where size is the size of the file
  buffer = (uint32_t*)malloc(size);

  // if buffer is null, has not been allocated correctly
  if (!buffer)
  {
    // memory error, typically game over
    fprintf(stderr, "Error allocating memory.\n");
    // exit with failure
    exit(EXIT_FAILURE);
  }

  // assert no emulator memory overflow
  if (size > 65536)
  {
    // output error to stdout
    fprintf(stderr, "Emulator memory overflow\n");
    // exit with a failure
    exit(EXIT_FAILURE);
  }

  // use fread to read to the buffer
  fread(buffer, size, size, arm_bin);
  // use fclose to end the feed from the file
  fclose(arm_bin);
  
  return buffer;
}

