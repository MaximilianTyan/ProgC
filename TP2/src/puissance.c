#include <stdio.h>

/*
* Brute force algorithm to compute raising integers to some power
* An optimised algrithm (fast power)is preferred in case of a large power
*/


int main() {
	
	short power = 4;
	long int number = 2;
	
	printf("Raising %lu to the power of %d\n", number, power);

	for (short i=0; i<power; i++) {
		number *= number;
	}
	
	printf("Result: %lu\n", number);

	return 0;
}
