#include <stdio.h>

/*
* Programme permettant d'accéder et de modifier
*/


int main() {
	
	int tabi[] 		= {0,1,2,3,4,5,6,7,8,9};
	float tabf[] 	= {0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0};
	
	for (short i=0; i < (short) (sizeof(tabi)/sizeof(int)); i += 2) {
		
		*(tabi + i) = *(tabi + i) * 3;
	}

	
	for (short i=0; i < (short) (sizeof(tabi)/sizeof(int)); i++) {
		printf("%d,", *(tabi + i));
	}
	printf("\n");

	for (short i=0; i < (short) (sizeof(tabf)/sizeof(float)); i += 2) {
		*(tabf + i) = *(tabf + i) * 3;
	}
	
	for (short i=0; i < (short) (sizeof(tabf)/sizeof(float)); i++) {
		printf("%f,", *(tabf + i));
	}
	printf("\n");

	return 0;
}
