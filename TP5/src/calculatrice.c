#include <stdio.h>
#include "calculatrice.h"

float calculate(char *expression) {
	float a, b;
	char op;
	sscanf(expression, "%f %c %f", &a, &op, &b);
	
	switch (op) {
	
	case '+':
		return a + b;

	case '-':
		return a - b;
	
	case '*':
		return a * b;
	
	case '/':
		return a / b;
	
	default:
		printf("'%c' operation not implemented", op);
return -1;
	}
}
