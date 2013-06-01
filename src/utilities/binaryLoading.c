///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: binaryLoading.c
// Group: 21
// Memebers: amv12, lmj112, skd212
//
// TODO - Move the 2^16 bits into a const
///////////////////////////////////////////////////////////////////////////////

FILE* openFile(char* path)
{
  // open the file
  FILE *file = fopen(path, "rb");
  return file;
}

int fileExists(char* path)
{
  FILE *file = openFile(path);
  if (!file)  { return 1; }
  fclose(file); return 0;
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

uint32_t* loadBinaryFile(char* path, uint32_t* memory)
{
  // declare variables
  // the binary file pointer
  FILE *arm_bin = 0;
  // the size of the binary file
  long unsigned int size = 0;
  arm_bin = openFile(path);

  // if the file is null
  if (fileExists(path) == 1)
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

  // if buffer is null, has not been allocated correctly
  if (!memory)
  {
    // memory error, typically game over
    fprintf(stderr, "Error allocating memory.\n");
    // exit with failure
    exit(EXIT_FAILURE);
  }
  // use fread to read to the buffer
  fread(memory, size, size, arm_bin);
  // use fclose to end the feed from the file
  fclose(arm_bin);
  return memory;
}

