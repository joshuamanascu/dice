#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>
#include "parser.h"
#include "roll.h"

char *INPUT; //Will hold a copy of the input

void errors(int);

int main(int argc, char *argv[]) {
	
	if (argc == 1) {
		errors(1);
		return 1;
	}
	
	if (argc == 2) //If the entire sequence is submitted as one input
	{
		INPUT = (char *)malloc(strlen(argv[1]) + 1);
		strcpy(INPUT, argv[1]);
	}
	else {
		int alloc = 0;
		
		for (int i = 1; i < argc; i++) { //Calculate space needed for INPUT
			alloc += strlen(argv[i]) + 1;
		}
		
		INPUT = (char *)malloc(alloc);
		//INPUT[0] = '\0';
		
		for (int i = 1; i < argc; i++) {
			strcat(INPUT, argv[i]);
			strcat(INPUT, " ");
		}
	}
	
	int size = parse(INPUT); // Number of terms parsed
	
	if (size < 0) {
		errors(2);
		return 2;
	}
	
	int err = set_info(size);
	
	if (err < 0) {
		errors(err);
		return err;
	}
	
	int tmp;
	int total = 0;
	
	int mult, num, sides;
	
	srand(time(0));
	
	//while (0 == 0) {}
	
	for (int i = 0; i < err; i++) {
		
		mult = rolls[i].choice.roll.mult;
		num = rolls[i].choice.roll.num;
		sides = rolls[i].choice.roll.sides;
		
		if (rolls[i].constant == 'c') {
			tmp = rolls[i].choice.value;
		}
		else if (rolls[i].constant == 'r') {
			tmp = roll(mult, num, sides);
		}
		
		if (rolls[i].ARITH == '+') {
			total += tmp;
		}
		else if (rolls[i].ARITH == '-') {
			total -= tmp;
		}
		else if (i == 0 && rolls[i].ARITH == '\0') {
			total += tmp;
		}
	}
	
	printf("%d\n", total);
	
	free(INPUT);
	
	return 0; // Success
}

void errors(int code) {
	if (code == 1) {
		printf("No input received. Please provide input.\n");
	}
	else if (code == 2) {
		printf("Error reading input. Please try again.\n");
	}
	else if (code == -3) {
		printf("Input error: Incorrect format.\n");
	}
	else if (code == -4) {
		printf("Input error: A number is out of range\n");
	}
	else if (code == -5) {
		printf("Input error: Attempting to roll a 0-sided die\n");
	}
	
	//exit(code);
	
}
