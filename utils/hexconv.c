#include <stdio.h>

void hexconv(int value) {
	short size = sizeof(value);

	printf("(%d)_10 = ( ", value);
	for (short i=0; i < size; i++) {
		printf("%x ", (unsigned char) (value >> (size-1 - i)*8 ));
	}
	printf(" )_16\n");

	return 0;
}
