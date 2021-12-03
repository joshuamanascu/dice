#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "parser.h"

int TOTAL; // Dice value
char *INPUT; //Will hold a copy of the input

int main(int argc, char *argv[]) {
	
	INPUT = (char *)malloc(strlen(argv[1]) + 1);
	strcpy(INPUT, argv[1]);
	
	int size = parse(INPUT); // Number of terms parsed
}

void errors(int code) {
	if (code == 1) {
		printf("No input received. Please provide input");
	}
	
}
