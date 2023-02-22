#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>

#include "pancake.h"

/*PRINT function*/	
void
print(int *counter, unsigned int *memory, int *skipper)
{
	unsigned int x = memory[*counter + 1];
	unsigned int y = (memory[(*counter + 2)])--;
	int portion_length = (x - y) / 2;

	if(*skipper){
		
		for(int i = 0; i < portion_length; i++){
		
			unsigned int memory_x = memory[( x + i )] + '0';
			unsigned int memory_y = memory[( y - i )] + '0';

			putchar(memory_x);
			putchar(memory_y);
		}

	} 

	/*update counter and skipper*/
	*skipper = 1;
	*counter += 3;


}

/*FLIP function*/
void
flip(int *counter, unsigned int *memory, int *skipper)
{
	/*flip memory from x to y point*/
	unsigned int x = memory[*counter + 1];
	unsigned int y = (memory[( *counter + 2 )])--;
	int portion_length = (x - y) / 2;

	if(*skipper){
	
		for(int i = 0; i < portion_length; i++){
		
			unsigned int memory_x = memory[( x + i )];
			unsigned int memory_y = memory[( y - i )];
	
			memory[( y - i )] = memory_x;
			memory[( x + i )] = memory_y;
		}

	} 	

	/*update counter and skipper*/
	*skipper = 1;
	*counter += 3;
}

void 
runPancakeProgram(unsigned int *memory)
{
	/*keep track of the length and index counter*/
	unsigned int *m = memory;
	int counter = 0;
	int skipper = 1; /*keep track of skips*/

	while ((m[counter] < STOP) || ((skipper = 0) && (m[counter] >= STOP))){

		if(m[counter] == SKIP){

			unsigned int x = m[counter++];
			unsigned int y = m[( counter + 2 )];

			if(m[x] > m[y]){
				skipper = 0;
			} 

		}else if( m[counter] == FLIP){

			flip(&counter, &m, &skipper); 

		} else if (m[counter] == PRINT){

			print(&counter, &m, &skipper);

		} else if (m[counter] == JUMP) {

			if(skipper){
				
				unsigned int x = m[counter++];
				counter = x;

			} else {

				skipper = 1;
				counter += 2;

			}
		} else {
			
			skipper = 1;
			counter++;
		}
	} 

}

