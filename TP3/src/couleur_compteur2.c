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
	couleurs[2] = couleurs[0];

	short sizec = sizeof(couleurs) / sizeof(struct color);
	
	struct color distinct[sizec];
	int effectif[sizec];
	
	// On mets les valeurs de la liste à 0 pour éviter les valeurs parasites pouvant exister
	for (short i=0; i<sizec; i++) {
		distinct[i].r = couleurs[0].r;
		distinct[i].g = couleurs[0].g;
		distinct[i].b = couleurs[0].b;
		distinct[i].a = couleurs[0].a;
		effectif[i] = 0;
	}
	effectif[0] = 1;
	
	for (short i=1; i < sizec; i++) {
		for (short j=0; j <= i; j++) {
			if ( ! ( couleurs[i].r != distinct[j].r
					|| couleurs[i].g != distinct[j].g
					|| couleurs[i].b != distinct[j].b
					|| couleurs[i].a != distinct[j].a) ) {
					// S'il n'y a pas 1 seule différence <=> couleurs égales
				effectif[j] += 1;
				break;
			} else if (j == i) {
				// le dernier élément de distinct est différent de la couleur <=> nouvelle couleur
				distinct[j] = couleurs[i];
				effectif[j] += 1;
			}
		}
	}
	
	printf("Couleurs différentes:\n");
	for (short i=0; i < sizec; i++) {
		if (effectif[i] != 0) {
			printf("0x%02x 0x%02x 0x%02x 0x%02x: %d\n", distinct[i].r, distinct[i].g, distinct[i].b, distinct[i].a, effectif[i]);
		}
	}

	return 0;
}

