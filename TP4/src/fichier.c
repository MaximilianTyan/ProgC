#include <stdio.h>
#include <fcntl.h> 	// for options constants (RDONLY ...)
#include <unistd.h>	// for open, close, read, write ...
#include <string.h>

#include "fichier.h"

void lire_fichier(char *fichier) {
	int fd = open(fichier, O_RDONLY);
	char z;
	int size = 0;
	do {
		size = read(fd, &z, 1);
		printf("%c", z);
	} while (size > 0);
	printf("\n");
	close(fd);
}

void ecrire_dans_fichier(char *fichier, char *message) {
	// On ouvre le fichier où écrire (en le créant si besoin)
	// On donne également les permissions de lecture et d'écriture à l'utilisateur
	int fd = open(fichier, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	
	// On utilise a librairie string.h avec strlen pour obtenir la taille
	// car un sizeof simple ne marcherait pas
	write(fd, message, strlen(message));
	
	close(fd);
}

