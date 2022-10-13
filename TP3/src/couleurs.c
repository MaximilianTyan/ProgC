#include <stdio.h>

struct color {
	char r;
	char g;
	char b;
	char a;
};


int main() {
	struct color couleurs[10];

	for (short i=0; i<10; i++) {
		couleurs[i].r = i * 15;
		couleurs[i].g = i * 15;
		couleurs[i].b = i * 15;
		couleurs[i].a = i * 15;
	}
	
	return 0;
}
