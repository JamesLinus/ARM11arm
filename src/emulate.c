#include <stdlib.h>

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
