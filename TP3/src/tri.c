#include <stdio.h>
#include <stdlib.h>

/*
* Programme générant un tableau d'entiers aléatoires entre 1 et 100 et le triant
* en utilisant le tri à bulle (bubble sort)
*/


char verif(int arr[], size_t size) {
	
	short limit = size / sizeof(int) ;
	for (short i=1;		i < limit 	; i++) {
		
		// If one term in the wrong order => unsorted
		if (arr[i-1] > arr[i]) {
			return 0;
		}
	}
	return 1;
}

void bubble(int arr[], size_t size) {
	int tmp;
	int iterations = 0;
	while (!verif(arr, size)){
		
		short limit = size / sizeof(int) ;
		for (short i=1;  i < limit ; i++) {
			
			// if prev > next invert the terms
			if (arr[i-1] > arr[i]) {
				tmp = arr[i];
				arr[i] = arr[i-1];
				arr[i-1] = tmp;
			}
		}
		iterations++;
	}
	printf("Sorted in %d cycles\n", iterations);
}


int main() {
	int arr[100];
	short limit;

	printf("INITIAL: [");
	limit = sizeof(arr) / sizeof(int);
	for (short i=0; 	i < limit; 	i++) {
		arr[i] = (int) (100 * (float) rand()/RAND_MAX);
		printf("%d, ", arr[i]);
	}
	printf("]\n");
	printf("SORTED:%s\n", verif(arr, sizeof(arr)) ? "TRUE" : "FALSE");
	
	bubble(arr, sizeof(arr));
	
	printf("POST: [");
	limit = sizeof(arr)/ sizeof(int);
	for (short i=0; i < limit ; i++) {
		printf("%d, ", arr[i]);
	}
	printf("]\n");
	printf("SORTED:%s\n", verif(arr, sizeof(arr)) ? "TRUE" : "FALSE");

	return 0;
}



