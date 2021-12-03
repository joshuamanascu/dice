#include <stdlib.h>
#include <string.h>
#include "parser.h"

//char **TERMS;

void dynamicAlloc(int);
	
//Parses the input and stores each term as an entry in the array TERMS. Returns the number of elements in TERMS.
int parse(char *input) { 
	int count = 0;
	dynamicAlloc(10);
	
	char *token;
	token = strtok(input, " ");

	while (token != NULL) {
		TERMS[count] = strdup(token);
		count++;
		
		token = strtok(NULL, " ");
		
		if (count % 10 == 0) dynamicAlloc(count + 10);
	}
	
	return count;
}

void dynamicAlloc(int slots) {
	TERMS = (char**)realloc(TERMS, sizeof(char *) * slots);
}


