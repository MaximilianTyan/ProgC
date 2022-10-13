#include <stdio.h>

/*
* Affichage de la taille des différents types de variables
* disponibles en langage C.
*/

int main() {
	// 'sizeof' retourne une variable 'long unsigned'	
	printf("sizeof char  			= %lu octets\n", sizeof(char));
	printf("sizeof short 			= %lu octets\n", sizeof(short));
	printf("sizeof int   			= %lu octets\n", sizeof(int));
	printf("sizeof long int 		= %lu octets\n", sizeof(long int));
	printf("sizeof long long int	= %lu octets\n", sizeof(long long int));
	printf("sizeof float			= %lu octets\n", sizeof(float));
	printf("sizeof double			= %lu octets\n", sizeof(double));
	printf("sizeof long double		= %lu octets\n", sizeof(long double));
	
	return 0;
}
