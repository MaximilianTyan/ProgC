#include <stdio.h>
//#include "bitconv.h"
/*
* Programme pour expérimenter avec la déclaration de
* variables de différents types, signées ou non ainsi
* que leur formatage et leur affichage avec des
* pointeurs.
*/

void showhex(char *ptr, long int size) {
	printf("HEX: ");
	for (int i=0; i < size; i++) {
		printf("%x ", (unsigned char) *(ptr + (size - 1) - i));
	}
	printf("\n");
}


int main() {
	signed char cvar = 'a';
	printf("signed char variable: 		%c\t\t\t", cvar);
	showhex((char*) &cvar, sizeof(cvar));
	//showbits(cvar);

	unsigned char ucvar = 'a';
	printf("unsigned char variable: 	%c\t\t\t", ucvar);
	showhex((char*) &ucvar, sizeof(ucvar));
	//showbits(ucvar);

	signed short svar = -3;
	printf("signed short variable: 		%hi\t\t\t", svar);
	showhex((char*) &svar, sizeof(svar));
	//showbits(svar);

	unsigned short usvar = 3;
	printf("unsigned short variable: 	%hu\t\t\t", usvar);
	showhex((char*) &usvar, sizeof(usvar));
	//showbits(usvar);

	signed int ivar = -124;
	printf("signed int variable: 		%i\t\t\t", ivar);
	showhex((char*) &ivar, sizeof(ivar));
	//showbits(ivar);

	unsigned int uivar = -124;
	printf("unsigned int variable: 		%u\t\t", uivar);
	showhex((char*) &uivar, sizeof(uivar));
	//showbits(uivar);

	signed long int livar = 1024;
	printf("signed long int varible: 	%li\t\t\t", livar);
	showhex((char*) &livar, sizeof(livar));
	//showbits(livar);
	
	unsigned long int ulivar = -2328;
	printf("unsigned long int varible: 	%lu\t", ulivar);
	showhex((char*) &ulivar, sizeof(ulivar));
	//showbits(ulivar);
	
	signed long long int llivar = 314159272;
	printf("signed long long int variable 	%lli\t\t", llivar);
	showhex((char*) &llivar, sizeof(llivar));
	//showbits(llivar);

	unsigned long long int ullivar = -615735672;
	printf("unsigned long long int variable %llu\t", ullivar);
	showhex((char*) &ullivar, sizeof(ullivar));
	//showbits(ullivar);

	float fvar = -2.35;
	printf("float: 				%f\t\t", fvar);
	showhex((char*) &fvar, sizeof(fvar));
	//showbits(fvar);

	double dvar = -2.98732;
	printf("double: 			%g\t\t", dvar);
	showhex((char*) &dvar, sizeof(dvar));
	//showbits(dvar);

	long double ldvar = -2.123456789123456;
	printf("long double: 			%Lg\t\t", ldvar);
	showhex((char*) &ldvar, sizeof(ldvar));
	//showbits(ldvar);
	
	return 0;
}
