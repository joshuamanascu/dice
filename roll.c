#include <stdlib.h>
#include <math.h>
#include "roll.h"


//Rolls the dice
//num represents the number of dice rolled
//sides represents how many sides the dice has
int roll(int mult, int num, int sides) {
	
	int total = 0;
	
	for (int i = 0; i < mult; i++) {
		for (int j = 0; j < num; j++) {
			double uni = rand() / (RAND_MAX + 1.0); // Generates random float in [0,1[
		
			total += (int)((uni * sides) + 1); // Random int in [1,sides]
		}
	}
	
	return total;
	
}


