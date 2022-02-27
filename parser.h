char **TERMS;

int parse(char *input);
int set_info(int number);

struct INFO {
	char ARITH; // + for addition, - for substraction, 0 for not set
	
	char constant; // Set to 'c' for constant, and 'r' for roll
	
	union CHOICE {
		struct ROLL {
			int sides; // Sides of the dice roll. Set to 0 if it's a constant
			int num; //Number of times to roll the dice and add to the total.
			int mult; //Number of times to repeat the roll.
		}roll;
		
		int value; // Value for the constant
	}choice;
};

struct INFO *rolls;
