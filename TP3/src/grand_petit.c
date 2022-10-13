#include <stdio.h>
#include <stdlib.h>

int main() {

	int tab[100];
	for (short i=0; i<100; i++) {
		tab[i] = rand();
	}
	
	int min = tab[0], max = tab[0];
	short int imin = 0, imax = 0;

	for (short i=0; i < (short)(sizeof(tab)/sizeof(int)); i++) {
		if (min > tab[i]) {
			min = tab[i];
			imin = i;
		}
		if (max < tab[i]) {
			max = tab[i];
			imax = i;
		}
	}
	
	printf("Max: Tab[%hu] = %d\n", imax, max);
	printf("Min: Tab[%hu] = %d\n", imin, min);

	return 0;
}
