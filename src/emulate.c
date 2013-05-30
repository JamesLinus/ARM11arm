///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: emulate.c
// Group: 21
// Memebers: amv12, lmj112, skd212
//
// TODO
//   - Required to improve error checking for ftell
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "arm.h"

void loadBinaryFile(char* path){
	FILE *file;

	file = fopen(path, "b");
	if (file) {
    	fread(buffer, MAX_FILE_SIZE, 1, file);
	}
	else {
  	  // file opneing error
	}

int main(int argc, char **argv) {

	
  	return EXIT_SUCCESS;
}
