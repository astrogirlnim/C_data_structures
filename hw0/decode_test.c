//Include libraries
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>


/* This script decodes run-length encoding stream*/
int
main(int argc, char **argv)
{
	if(argc < 2 )
	{
		fprintf(stderr, "Usage: %s\n file.in", argv[0]);
		return 1;
	}

	int current; /* current character in stdin stream */
	int next; /* next character in stdin stream*/

	while((current = getchar()) != EOF){

		/* Check for a digit */
		if(isdigit(current)) {
			
			/* counter variable for character repeats*/
			int count = 0;

			count = count * 10 + current - '0';

			/* Print count # of copies of the next character if not at the end of file */
			for(int i = 0; i < count; i++){
				putchar(next);
			}
		
		} else {
		/* Copy character directly */
			putchar(current);
		}
	}

	return 0;
}

