#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>

#include "pancake.h"

/*PRINT function*/	
int
print(int counter, unsigned int *memory, int skipper)
{
	int x = memory[counter + 1];
	int y = (memory[counter + 2]) - 1;

	if(skipper){

		while(x < y){
			
			printf("%u ", memory[x]);
			x++;
		}
		if (x == y) printf("%u", memory[x]); /*print last statement without whitespace*/
		printf("\n");

	} 

	return counter += 3;


}

/*FLIP function*/
int
flip(int counter, unsigned int *memory, int skipper)
{
	/*flip memory from x to y point*/
	int x = memory[counter + 1];
	int y = memory[(counter + 2)] - 1;

	if(skipper){
		
		int tmp; /*buffer for memory array reversal*/

		while(x < y){

			tmp = memory[x];
			memory[x] = memory[y];
			memory[y] = tmp;
			x++;
			y--;

		}

	} 	

	return counter += 3;
}

void 
runPancakeProgram(unsigned int *memory)
{
	int counter = 0; /*array index tracker*/
	int skipper = 1; /*keep track of skips*/

	while ((memory[counter] < STOP) || ((skipper == 0) && (memory[counter] >= STOP))){

		/* STOP is skipped */
		if ((skipper == 0) && (memory[counter] >= STOP))
		 {
			 skipper = 1;
			 counter++;

		/* SKIP */
		 } else if(memory[counter] == SKIP){

			unsigned int x = memory[counter + 1];
			unsigned int y = memory[( counter + 2 )];

			if((memory[x] > memory[y]) && (skipper) ){
				
				skipper = 0;

			} else {

				skipper = 1;
			
			}

			counter += 3;

		/* FLIP */
		}else if( memory[counter] == FLIP){

			counter = flip(counter, memory, skipper);
			skipper = 1;

		/* PRINT */
		} else if (memory[counter] == PRINT){

			counter = print(counter, memory, skipper);
			skipper = 1;

		/* JUMP */
		} else if (memory[counter] == JUMP) {

			if(skipper){
				
				unsigned int x = memory[counter + 1];
				counter = x;

			} else {

				skipper = 1;
				counter += 2;

			}
		}
	} 
}

