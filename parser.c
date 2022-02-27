#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "parser.h"
#include <time.h>
#include <ctype.h>
#include <errno.h>


void dynamicAlloc(int);
void freeTERMS(int);
	
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
	
	dynamicAlloc(count);
	
	return count;
}

//Sets rolls array and parses each term into a cell. Returns number of cells on success and <0 on error.
int set_info(int number) {
	rolls = malloc(sizeof(struct INFO) * number); // Allocate enough memory to rolls
	
	int count = 0; //Tracking size of the rolls array
	
	for (int i = 0; i < number; i++) {
		char *current = strdup(TERMS[i]);
		// x -> axbdc, n -> bdc, d -> dc, w-> axdc c -> c, 0 -> not set
		char format = '0';
		
		// Set ARITH if needed
		if (*current == '+' || *current == '-') {
			rolls[count].ARITH = *current;
			current++;
			TERMS[i]++; //Get rid of arithmetic sign at the front of the term
			
			if (*current == '\0') continue;
		}
		
		if (isdigit(*current) || *current == 'd') {
			
			if (*current == 'd') format = 'd';
			else {
				while (isdigit(*current)) {current++;} // Run through the number, if needed
				if (*current == '\0') {format = 'c';} // Constant
			}
			
			while (*current != '\0') {
				switch(*current) {
					case 'x':
						current++;
						if (isdigit(*current)) {
							format = 'x';
							while (isdigit(*current)) {current++;}
						}
						else {format = 'w';}
						
						break;
						
					case 'd':
						current++;
						if (isdigit(*current)) {
							while (isdigit(*current)) {current++;}
						}
						else {return -3;}
						
						if (*current != '\0') {return -3;} //Must be ended to be valid
						
						if (format == '0') format = 'n'; //If no format has been set by now, then it's bdc
						
						break;
						
					default:
						return -3; //Format Error
				}
			}
		}
		else {return -3;} // Error, bad input 
		
		int mult = 1, num = 1, sides = 0;
		int err;
		//Scan into the INFO struct now, based on format
		switch (format) {
			case 'x':
				err = sscanf(TERMS[i], "%dx%dd%d", &mult, &num, &sides);
				break;
				
			case 'w':
				err = sscanf(TERMS[i], "%dxd%d", &mult, &sides);
				break;
				
			case 'n':
				err = sscanf(TERMS[i], "%dd%d", &num, &sides);
				break;
				
			case 'd':
				err = sscanf(TERMS[i], "d%d", &sides);
				break;
			
			case 'c':
				rolls[count].constant = 'c';
				err = sscanf(TERMS[i], "%d", &rolls[count].choice.value);
				break;
				
			default:
				return -3; //Input error
		}
		
		if (sides == 0 && format != 'c') return -5; // Attempt to roll 0-sided die
		
		if (err == EOF){
			if (errno == ERANGE) return -4; // Out of range int
			else return -3;
		}
		
		if (format != 'c') {
			rolls[count].constant = 'r';
			rolls[count].choice.roll.mult = mult;
			rolls[count].choice.roll.num = num;
			rolls[count].choice.roll.sides = sides;
		}
		
		count++;
	}
	
	rolls = realloc(rolls, sizeof(struct INFO) * count);
	freeTERMS(number);
	return count;
}

void dynamicAlloc(int slots) {
	TERMS = (char**)realloc(TERMS, sizeof(char *) * slots);
}

void freeTERMS(int size) {
	for (int i = 0; i < size; i++) {
		if(strcmp(TERMS[i], "") != 0) free(TERMS[i]); //free(empty string) causes problems
		else free(TERMS[i] - 1);
	}
	free(TERMS);
}


