//Instructions on how to compile: run "c99 -g -Wall -pedantic -o sumRange sumRange.c"

//Libraries
#include <stdio.h>
#include <stdlib.h>

int
sumRange(int start, int end)
{
	int i; // loop index
	int sum; //sum variable

	//Initialize sum
	sum = 0;

	for(i = start; i < end; i++){
		sum += i; //Add one per each new element in range
	}

	return sum;
}

int
main (int argc, char **argv)
{
	int start;
	int end;

	// Base case: error message returned if length < 3
	// Argument length is 3 given program name counts as an argument
	if(argc != 3){
		fprintf(stderr, "Usage: %s\n start end", argv[0]);
		return 1;
	}

	// Define start and end and convert to integers
	start = atoi(argv[1]);
	end = atoi(argv[2]);

	//Call helper function and print
	
	printf("sumRange(%d, %d) = %d\n", start, end, sumRange(start, end));
	
	return 0;

}
