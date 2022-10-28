#include "fichier.h"

int main() {

	char filepath[] = "./test.txt";
	lire_fichier(filepath);

	char writing[] = "This is a test";
	ecrire_dans_fichier("./res.txt", writing);
	lire_fichier("./res.txt");
	return 0;
}
