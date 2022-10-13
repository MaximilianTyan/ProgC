#include <stdio.h>

/*
* Programme qui convertir un nombre décimal fourni en entrée en hexdécimal
*/

int main() {
	
	int value;
	printf("Value to convert: ");
	scanf("%d", &value);
	printf("Value: %d\n", value);
	
	short size = sizeof(value);
	char *ptr = (char *) &value;
	printf("Hex: ( ");
	for (short i=0; i < size; i++) {
		printf("%x ", (unsigned char) *(ptr + size-1 - i));
	}
	printf(")_16\n");

	return 0;
}
