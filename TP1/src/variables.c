#include <stdio.h>

/*
* Programme pour expérimenter avec la déclaration de
* variables de différents types, signées ou non ainsi
* que leur formatage 
*/


int main() {
	signed char cvar = 'a';
	printf("signed char variable: 		%c\n", cvar);
	
	unsigned char ucvar = 'a';
	printf("unsigned char variable: 	%c\n", ucvar);
	


	signed short svar = -3;
	printf("signed short variable: 		%hi\n", svar);

	unsigned short usvar = 3;
	printf("unsigned short variable: 	%hu\n", usvar);


	
	signed int ivar = -124;
	printf("signed int variable: 		%i\n", ivar);

	unsigned int uivar = -124;
	printf("unsigned int variable: 		%u\n", uivar);



	signed long int livar = 1024;
	printf("signed long int varible: 	%li\n", livar);
	
	unsigned long int ulivar = -2328;
	printf("unsigned long int varible: 	%lu\n", ulivar);


	
	signed long long int llivar = 314159272;
	printf("signed long long int variable 		%lli\n", llivar);

	unsigned long long int ullivar = -615735672;
	printf("unsigned long long int variable 	%llu\n", ullivar);



	float fvar = -2.35;
	printf("float: 			%f\n", fvar);


	double dvar = -2.98732;
	printf("double: 		%g\n", dvar);


	long double ldvar = -2.123456789123456;
	printf("long double: 		%Lg\n", ldvar);
	
	return 0;
}
