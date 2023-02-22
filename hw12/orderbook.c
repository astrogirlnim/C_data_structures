#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>

#include "orderBook.h"

// This code emulates a simplified electronic trading order book using heaps. 
// Negative numbers are stored in a packed array heap at negative heap.
// Positive numbers are stored in a packed array heap at positive heap.
// Resizing occurs according to the size and max_size variables;
typedef struct orderBook {
	size_t pos_size; // current size of the positive heap array
	size_t pos_max_size; // max size of the heap array, for resizing
	size_t neg_size; // current size of the negative heap array
	size_t neg_max_size; // max size of the negative heap array, for resizing
	int* pos_heap; // heap array of the positive numbers
	int* neg_heap; // heap array of the negative numbers
} *OrderBook;

// Create an empty book struct with size = 0 and a null heap array
OrderBook orderBookCreate(void){

	OrderBook book = malloc(sizeof(struct orderBook));
	book->pos_size = 0;
	book->neg_size = 0;
	book->pos_max_size = 1;
	book->neg_max_size = 1;
	book->pos_heap = NULL;
	book->neg_heap = NULL;
	return book;
}

// HEAP SORTING
// Heap sorting functions are similar to those found in heapsort.c, provided in the class notes.

// swamps two elements in an array 
static void
swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

static size_t
parent(size_t i)
{
    return (i-1)/2;
}

// Sorting function for inducing the heap to float up.
// Takes an absolute value of heap elements to allow for usage for both
// the negative and positive heap.
static void
floatUp(size_t i, int *heap)
{
    if(i != 0 && (heap[parent(i)] < heap[i])) {
        swap(&heap[parent(i)], &heap[i]);
        floatUp(parent(i), heap);
    }
}

static size_t
child(size_t i, int side)
{
    return 2*i + 1 + side;
}

// Floats elements down the heap.
static void
floatDown(size_t i, size_t n, int *heap)
{
    size_t bigger = child(i,0);

    // Check if the child is greater than n
    // Swap elements by comparing sizes.
    if(bigger < n) {
       
	    if(bigger + 1 < n && heap[bigger+1] > heap[bigger]) {
		    bigger = bigger + 1;
	    }

        if(heap[bigger] > heap[i]) {
            swap(&heap[bigger], &heap[i]);
            floatDown(bigger, n, heap);
        }
    }
}

void orderBookDestroy(OrderBook orderbook){
	
	// First, free the heap
	if(orderbook->pos_heap != NULL) free(orderbook->pos_heap);
	if(orderbook->neg_heap != NULL) free(orderbook->neg_heap);

	// Then, free the struct
	free(orderbook);
}

// Inserts new value into corresponding heap
// char input determines whether to input into the positive or negative heap
int
insertNewValue(OrderBook O, int price, char i){
	//inserting into positive heap
	if (i == 'p'){
	    
		if(O->pos_heap == NULL){
			
			int *new_heap = malloc(sizeof(int));
			new_heap[0] = price;
			O->pos_heap = new_heap;
			O->pos_size = 1;
			O->pos_max_size = 1;

		} else { 
		
			if(O->pos_size >= O->pos_max_size){
		    
				O->pos_max_size *= 2;
				O->pos_heap = realloc(O->pos_heap, O->pos_max_size * sizeof(int));
	    
			}
	    
			O->pos_heap[O->pos_size] = price;
			floatUp(O->pos_size, O->pos_heap);

			O->pos_size++;
		}

	} else {
		//inserting into negative heap
		if(O->neg_heap == NULL){

			int *new_heap = malloc(sizeof(int));
			new_heap[0] = price;
			O->neg_heap = new_heap;
			O->neg_size = 1;
			O->neg_max_size = 1;

		} else {
    		
			if(O->neg_size >= O->neg_max_size){
    			
				O->neg_max_size *= 2;
				O->neg_heap = realloc(O->neg_heap, O->neg_max_size * sizeof(int));
    		
			}

			O->neg_heap[O->neg_size] = price;
			floatUp(O->neg_size, O->neg_heap);
			
			O->neg_size++;
		}
	}

	return 0;
}

int
checkprice(OrderBook O, int price, int indicator){

	if(indicator){
		//Input price is negative

		if ( O->pos_size == 0){
		
			return insertNewValue(O, price, 'n');

		} else if(O->pos_heap[0] + price <= 0 ){

			//insert the value into the negative heap
			return insertNewValue(O, price, 'n');
		}
		
		// If it gets to this point, the top element of the heap is a good price
		int returnvalue = O->pos_heap[0];


		//Check the size of the heap and float down the new root if appropriate
		if(O->pos_size == 1) {
			O->pos_size = 0;

		} else {
			swap(&(O->pos_heap[0]), &(O->pos_heap[(O->pos_size) - 1]));
			O->pos_size--;
			floatDown(0, O->pos_size, O->pos_heap);
		}

		return returnvalue;

	}

	// If the input price is positive
	if ( O->neg_size == 0){

		return insertNewValue(O, price, 'p');

	} else if (O->neg_heap[0] + price <= 0 ){

		//insert the value into the positive heap
		return insertNewValue(O, price, 'p');
	} 
	
	// If it gets to this point, the top element of the heap is a good price
	int returnvalue = O->neg_heap[0];
	
	//Switch roots
	if(O->neg_size == 1) {
		O->neg_size = 0;
	} else {
		swap(&(O->neg_heap[0]), &(O->neg_heap[(O->neg_size - 1)]));
		O->neg_size--;
		floatDown(0, O->neg_size, O->neg_heap);
	}

	return returnvalue;
}

int orderBookInsert(OrderBook o, int price)
{
	// Check if the price is 0
	if (price == 0){
		return 0;
	} else if (price < 0){

		// Check the positive heap
		return checkprice(o, price, 1);

	} 

	return checkprice(o, price, 0);
	
}

