#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <math.h>

// This code creates a hash table whose items are key-value pairs.
// The keys will be of n length from a-z.
// The values, initially, will all be 0.


// hash table key-value pair struct
struct ht_pair{
	struct ht_pair *next;
	char* key;
	int* value;
};

// word array hash table struct
typedef struct wordArray{
	int size;
	int count;
	struct ht_pair *pairs;
} *WordArray;

// HASH TABLE INITIALIZATION FUNCTIONS

// Create a single hash table pair in the word array
// key is specified by input "const char k"
/*static 
ht_pair* Create_pair(const char* k) {

	ht_pair* new_pair = malloc(sizeof(ht_pair));
	assert(new_pair); //check for memory

	new_pair -> key = strdup(k);
	new_pair -> value = 0;
	return i;

}*/

// Create a key based off a past key
// Increments a string in place, returning 1 on overflow
// and 0 otherwise
//
// Examples:
//
// incKey("aaa") -> "aab"
// incKey("abc") -> "abd"
// incKey("abz") -> "aca"
// incKey("zzz") -> "aaa", returns 1
//int wordArrayIncKey(char *s);


// Create an empty word array based on key string length n
WordArray* emptyWordArrayCreate (unsigned int n){
	
	WordArray* w= malloc(sizeof(struct wordArray));
	
	// calculate the size
	w->size = fact(26) / (fact(n) * fact(26 - n));	
	w->count = 0;
	w->pairs = calloc((size_t)w->size, sizeof(struct ht_pair));

	//check for memory
	assert(w);

	return w;

}

// Create the word array
//WordArray wordArrayCreate(unsigned int n){

//}


// DELETION FUNCTIONS FOR THE HASH TABLE

// Destroys a single pair in the word array
static void singleWordArrayDestroy(struct ht_pair w){
	free(w->key);
	free(w->value);
	free(w);
}

// Destroys the entire word array
void wordArrayDestroy(WordArray w){
	
	for(int i = 0; i < w->size; i++){
		
		struct ht_pair pair = w->pairs[i];
		
		if (pair != NULL) {
			singleWordArrayDestroy(pair);
		}
	}

	free(w->pairs);
	free(w);
}

// Key length retrieval
//int wordArrayKeyLength(WordArray w);

// Array search function
// Returns a pointer to location in word array
// indexed by string key.
//
// If key is the wrong length, or contains
// characters that are not between MIN_KEY and MAX_KEY,
// returns 0.
//int *wordArrayRef(WordArray w, const char *key);


// returns malloc'd minimum key for w
// as a null-terminated string
//char *wordArrayMinKey(WordArray w);



// print the contents of an array,
// with one key and value on each line, as in
//
// aa 0
// ab 0
// ac 0
// ...
//
//void wordArrayPrint(WordArray w);
