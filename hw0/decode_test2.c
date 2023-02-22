#include <stdio.h>
#include <ctype.h>

/*This file decodes run-length stdin files*/
int
main(int argc, char **argv)
{	
	int c; /*current character*/
	int count = 0; /* number of repeats of the current character*/
	
	while((c = getchar()) != EOF){
		
		if(isdigit(c)){
			/*update repeat variable*/
			count = c - '0';
			
			/*get the following character*/
			c = getchar();
			
			/* Pass character through count amount of times*/
			for(int i = 0; i < count; i++){
				putchar(c);
			}
				
		} else {
			putchar(c);
		}
	}

	return 0;
}
