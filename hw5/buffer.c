#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "buffer.h"

typedef struct elt {
	struct elt *next; // pointer to next element in list
	char value; // stored character value
} *Element;

typedef struct buffer {
	int n; // number of elements in the list
	struct elt *top; // linked list of characters
	struct elt **cursor_array; //array of cursor index elements
} *Buffer;


// This code creates and manipulates a buffer array of characters.
// It is similar to the stack.c code provided as a class example.

// BUFFER CREATION

Buffer 
bufferCreate(size_t n)
{
	// create an empty buffer struct
	Buffer b = malloc(sizeof(struct buffer));
	assert(b);

	// initialize cursor array and null element
	b->top = '\0';
	struct elt **array = malloc(sizeof(struct elt *) * n);
	
	for(int i = 0; i < n; i++){
		array[i] = &(b->top);
	}

	b->cursor_array = array;

	return b;
}


// BUFFER DESTRUCTION

// remove an element from a nonempty element list
void
elementRemove(Buffer b){

	// free top element and move top of list	
	struct elt *tmp = b->top;
	b->top = tmp->next;
	free(tmp);
}

// check if list is empty
int
bufferEmpty(Buffer b)
{
	return b->top == '\0';
}

void
bufferDestroy(Buffer b)
{
	// empty element list first
	while(!bufferEmpty(b)) {
		elementRemove(b);
	}

	// Then free the remaining elements
	free(b->cursor_array);
	free(b)
}
