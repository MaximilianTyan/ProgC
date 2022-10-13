#include <stdio.h>

/*
* Programme de calculatrice permettant d'expérimenter avec les switch case
*/

int main() {
	// énumeration pour simplifier la saisie
	enum operation {add, sub, mul, div, mod, and, or, xor, not};

	int a = 3;
	int b = 5;
	enum operation op = div; 

	switch (op) {
	
	case 0:
		printf("%i + %i = %i\n", a, b, a+b);
		break;
	
	case 1:
		printf("%i - %i = %i\n", a, b, a-b);
		break;
	
	case 2:
		printf("%i * %i = %li\n", a, b, (long int) a * (long int) b);
		break;
	
	case 3:
		printf("%i / %i = %f\n", a, b, (float) a / (float) b);
		break;
	
	case 4:
		printf("%i %% %i = %i\n", a, b,  a%b);
		break;
	
	case 5:
		printf("%i & %i = %i\n", a, b,  a&b);
		break;
	
	case 6:
		printf("%i | %i = %i\n", a, b, a|b);
		break;
	
	case 7:
		printf("%i ^ %i = %i\n", a, b, a^b);
		break;
	
	case 8:
		printf("~%i = %i\n", a, ~a);
	}

	return 0;
}
