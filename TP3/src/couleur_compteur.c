#include <stdio.h>

struct color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};


int main() {
	struct color couleurs[10];
	
	for (short i=0; i<10; i++) {
		couleurs[i].r = i * 2;
		couleurs[i].g = i * 2;
		couleurs[i].b = i * 2;
		couleurs[i].a = i * 2;
	}

	couleurs[5] = couleurs[2];
	couleurs[4] = couleurs[8];
	couleurs[1] = couleurs[0];

	//printf("Couleurs initiales\n");
	short sizec = sizeof(couleurs) / sizeof(struct color);
	/*
	for (short i=0; i < sizec; i++) {
		printf("%x %x %x %x\n", couleurs[i].r, couleurs[i].g, couleurs[i].b, couleurs[i].a);
	}*/

	struct color distinct[sizec];
	int effectif[sizec];
	
	// On mets les valeurs de la liste à 0 pour éviter les valeurs parasites pouvant exister
	for (short i=0; i<sizec; i++) {
		distinct[i].r = 0;
		distinct[i].g = 0;
		distinct[i].b = 0;
		distinct[i].a = 0;
		effectif[i] = 0;
	}
	/*
	printf("\nCouleurs distinctes\n");
	for (short i=0; i < sizec; i++) {
		printf("%x %x %x %x : %d\n", distinct[i].r, distinct[i].g, distinct[i].b, distinct[i].a, effectif[i]);
	}*/
	
	//printf("\nItérations\n");
	for (short i=0; i < sizec; i++) {
		//printf("--------------------------\n");
		for (short j=0; j <= i; j++) {
			//printf("i: %d, j: %d \t Color: %x Distinct: %x\n", i, j, couleurs[i].r, distinct[j].r);
			if ( ! ( couleurs[i].r != distinct[j].r
					|| couleurs[i].g != distinct[j].g
					|| couleurs[i].b != distinct[j].b
					|| couleurs[i].a != distinct[j].a) ) {
					// S'il n'y a pas 1 seule différence <=> couleurs égales
				effectif[j] += 1;
				//printf("COLOUR FOUND\n");
				break;
			} else if (j == i) {
				// le dernier élément de distinct est différent de la couleur <=> nouvelle couleur
				distinct[j] = couleurs[i];
				effectif[j] += 1;
				//printf("NEW COLOR\n");
			}
		}
		/*
		for (short i=0; i < sizec; i++) {
			printf("%x ", distinct[i].r);
		}
		printf("\n");
		for (short i=0; i < sizec; i++) {
			printf("%d ", effectif[i]);
		}
		printf("\n");
		*/
	}
	
	printf("Couleurs différentes:\n");
	for (short i=0; i < sizec; i++) {
		if (effectif[i] != 0) {
			printf(" 0x%02x 0x%02x 0x%02x 0x%02x: %d\n", distinct[i].r, distinct[i].g, distinct[i].b, distinct[i].a, effectif[i]);
		}
	}

	return 0;
}

