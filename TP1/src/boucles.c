#include <stdio.h>

/*
* Programme permettant d'afficher un triangle dans la console
* en utilisant différentes boucles (for et do while)
* La taille du triangle est réglable
* Exemple de triangle:
* taille 5
* 	*
* 	* *
* 	* # *
* 	* # # *
* 	* * * * *
*/

int main() {
	int length = 5;

	// for loop only
	printf("Triangle with for loop\n");

	for (int i=1; i < length+1; i++) {
		for (int j=0; j < i; j++) {
			if (j == 0 || j == i-1 || i == length) {
				printf("* ");
			} else {
				printf("# ");
			}
		}
		printf("\n");
	}
	
	// do while loop
	printf("Triangle with only do while look\n");

	int i = 1;
	do {
		int j = 0;
		do {
			if (j == i-1) {
				printf("*\n");
			} else if (i == length || j == 0) {
				printf("* ");
			} else {
				printf("# ");
			}
			j++;
		} while (j < i);
		
		i++;
	} while (i < length+1);

	return 0;
}


