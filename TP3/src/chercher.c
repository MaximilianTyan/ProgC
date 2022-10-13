#include <stdio.h>
#include <stdlib.h>

/*
* Programme pour rechercher une valeur dans un tableau
*/


int find(int target, int arr[], size_t size) {
	for (short i=0;     i < (short) size;  i++) {
		if ( arr[i] == target) {
			return i;
		}
	}
	return -1;
}


int main() {
	int arr[100];
	
	printf("array: [");
	short limit = sizeof(arr) / sizeof(int);
	for (short i=0;     i < limit;  i++) {
		arr[i] = (int) (100 * (float) rand()/RAND_MAX);
		printf("%d, ", arr[i]);
	}
	printf("]\n");

	int target = 10;
	int index = find(target, arr, sizeof(arr));
	
	if (index != -1) {
		printf("Value %d found in array at index %hu\n", target, index);
	}
	else {
		printf("Value %d not found in array\n", target);
	}

	return 0;
}
