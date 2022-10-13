#include <stdio.h>

/*
* Libairie permettant de représenter en base 2 les
* éléments fournis (chiffres et caractères).
* Ce programme utilise un masque pour exploiter la représentation
* binaire des nombres dans un ordinateur plutôt que de passer par
* ddes modulos ou divisions succèssives
*/


void showbits(long long int num) {
	
	
	short limit = (short) sizeof(num) * 8;
	unsigned int mask = 1 << (limit-1);

	printf("(%i)_10 = (", num);
	for (short i=0; i < limit; i++) {
		if (i % 8 == 0) {
			printf(" ");
		}
		printf("%i", (num & mask) != 0);
		mask = mask >> 1;
	}
	printf(" )_2\n");
}
