#include <stdio.h>

/*
* Programme qui calcule et affiche les n premières valeurs de la
* suite de fibonacci (n>=2).
*/


int main() {
	int n = 30;
	
	int Unprev2 = 0;
	int Unprev = 1;
	int Un;
	
	printf("n:0\tUn=%d\n", Unprev2);
	printf("n:1\tUn=%d\n", Unprev);

	for (int i=2; i<n; i++) {
		Un = Unprev + Unprev2;
		Unprev2 = Unprev;
		Unprev = Un;
		printf("n:%i\tUn=%d\n", i, Un);
	}

	return 0;
}
