#include <stdio.h>

/*
* Programme pour prendre en main les différents opérateurs
* ainsi que les différents comportements en fonction des
* types de variables
*/

int main() {
	
	int a = 16;
	int b = 3;

	int add = a + b;
	printf("a + b = %i\n", add);
	
	signed int sub = a - b;
	printf("a - b = %i\n", sub);
	
	long int mul = a * b;
	printf("a * b = %li\n", mul);
	
	float div = (float) a / (float) b;
	printf("a / b = %f\n", div);
	
	int mod = a % b;
	printf("a %% b = %i\n", mod);	
	
	int and = a & b;
	printf("a & b = %i\n", and);

	int or = a | b;
	printf("a | b = %i\n", or);

	int xor = a ^ b;
	printf("a ^ b = %i\n", xor);

	int not = ~a;
	printf("~a = %i\n", not);	

	return 0;
}
