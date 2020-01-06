#include <iostream>
#include <stdlib.h>
#include <time.h>

#define MONTECARLO_ITERATION 100

int main() {
	int numbers[MONTECARLO_ITERATION];
	srand(time(NULL));
	for (int i = 0; i < MONTECARLO_ITERATION; i++) {
		numbers[i] = rand() % 200 + 1;	// Generates number from 1 to 200
	}

	system("pause");
	return 0;
}