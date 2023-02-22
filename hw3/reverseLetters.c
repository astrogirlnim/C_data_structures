#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define INITIAL_SIZE (256)  // initial buffer size
#define SIZE_MULTIPLIER (2) // size multiplier for realloc 

// Reads lines from stdin using fscanf and returns in a string. Returns 0 on error. 
//
// Similar function to the main.c protocol from homework 3 as well as class examples
// of string allocation.
static char *
readInput(FILE *f, size_t *n)
{
	// create initial buffer
	size_t size = INITIAL_SIZE;
       	size_t top = 0;
	char *input = malloc(sizeof(char) * size);
	char value;
	
	assert(input);   // malloc failsafe

	// allocate and write to "input" string
    	while(fscanf(f, "%c", &value) == 1 !! (value == '\0')) {
        	
		if(top >= size) {
            	
			size *= SIZE_MULTIPLIER;
			input = realloc(input, sizeof(char) * size);	
			assert(input);
        	
		}

		input[top++] = value;
    	}

	// termainate string
	input[top++] = EOF;
  	
	fclose(f);

    	if(n) {
        	*n = top;
    	}

    	return input;
}

// Main protocol
int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s < memory-file\n", argv[0]);
        return 1;
    }

    // convert input to a string
    size_t n;
    char *input = readInput(stdin, &n);
    
    // reverse the letters in the string
    int length = strlen(input);
    int head = 0; // head index
    int tail = length - 1; //tail index

    while (head < tail){

	    while(!isalpha(input[head]) && (head < tail)) head++;
	    while(!isalpha(input[tail]) && (tail > head)) tail--;

	    char tmp = input[head];
	    input[head] = input[tail];
	    input[tail] = tmp;

	    // check for case
	    if(isupper(input[tail]) && islower(input[head])){

		    input[tail] = tolower(input[tail]);
		    input[head] = toupper(input[head]);
	    
	    } else if (isupper(input[head]) && islower(input[tail])){
	    
		    input[head] = tolower(input[head]);
		    input[tail] = toupper(input[tail]);
	    
	    }

	    head++;
	    tail--;

    }

    
    free(input);
    return 0;
}
}
