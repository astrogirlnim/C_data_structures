#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <inttypes.h>

// gets each line from stdin into a malloc'd string
// Similar to getLine function in the class notes.
char *
getLine(void)
{
	char *line;
	size_t size = 2;
	size_t length = 0;
	int c;

	line = malloc(size);
	assert(line);

	// Get each character and allocate to line
	while((c = getchar()) != EOF && c != '\n') {
		
		if(length >= size-1) {

			//incease the space
			size *= 2;
			
			//copy contents and reallocate size	
			line = realloc(line, size);
		}
	

        line[length++] = c;

	}

	line[length] = '\0';

	return line;
}

int
main(int argc, char **argv)
{
	//check for the correct number of inputs
	if(argc != 1){
		fprintf(stderr, "Usage: %s salt\n", argv[0]);
		return 1;
	}

	// read a line from the file
	char *line = getLine();

	puts(line);

	free(line);

	return 0;

}
