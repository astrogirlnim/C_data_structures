//Include libraries
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

// Better for C compiler: put the function before main instead of initializing
int
getNumber(void){
	int c;
	int num = 0;

	//keep reading until you get a digit
	while ((c = getchar()) !=  EOF && isdigit(c)) {
		num = num * 10 + (c - '0');
	}
	
	//put back character
	ungetc(c, stdin);

	return num;
}

int 
main(int argc, char **argv)
{
	if(argc !=1){
		fprintf(stderr, "Usage: %s\n", argv[0]);
		return 1;
	} 

	//read in numbers one character at a time and print them
	int num = 0;
	int c;

	while((c = getchar()) != EOF){
		if (isdigit(c)){
			num = num * 10 + (c - '0');
		} else if (c == '.') {
			//print accumulated number
			printf("[%d]", num);
		} else {
			putchar(c);
		}
	}

	return 0;
}








