#include <stdio.h>

/*
* Programme permettant de déterminer la divisibilité des
* nombres de 0 à 10000 tout en se familiarisant avec
* les conditions logiques
*/

int main() {

	for (int i=0; i<1000; i++) {
		if (i % 2 && i % 15) {
			printf("%i, ", i);
		}
	}
	printf("\nSont divisibles par 2 et 15\n");
	
	for (int i=0; i<1000; i++) {
		if (i % 103 == 0 || i % 107) {
			printf("%i, ", i);
		}
	}
	printf("\nSont divisibles par 103 ou 107\n");	

	for (int i=0; i<1000; i++) {
		if ( (i % 103 == 0 || i % 107) && (i % 3 != 0)) {
			printf("%i, ", i);
		}
	}
	printf("\nSont divisibles par 7 ou 5 mais pas 3\n");

	return 0;
}
