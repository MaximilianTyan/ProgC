#include <stdio.h>

// On défini la constante PI
#define PI 3.14159265358979

/*
* Programme pour calculer le périmètre et l'aire d'un
* cercle dont le rayon est donné (hard code)
*/


int main() {
	float rayon = 1;

	float perimeter = 2 * PI * rayon;

	float area = PI * rayon * rayon;

	printf("Rayon du cercle: %f\n", rayon);
	printf("Périmètre du cercle: %f\n", perimeter);
	printf("Aire du cerlce: %f\n", area);

	return 0;
}
