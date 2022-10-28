#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fichier.h"

struct marks {
	short ProgC;
	short SysEx;
};

struct student {
	char firstname[20];
	char name[20];
	char address[50];
	struct marks marks;
};

char *strip(char *str) {
	*(str + strlen(str) - 1) = "\0";
	return str;
}

int main() {
	printf("Nombre d'édutiants à entrer: ");
	int tabsize;
	scanf("%d", &tabsize);
	
	struct student etudiants[tabsize];

	for (int i=0; i < tabsize; i++) {
		printf("Etudiant %d: Prénom de l'étudiant >", i+1);
		char firstname[20];
		scanf(" %s", &firstname[0]);
		strcpy(&etudiants[i].firstname[0], strip(firstname));
		
		char name[20];
		printf("Etudiant %d: Nom de l'étudiant >", i+1);
		scanf(" %s", &name[0]);
		strcpy(&etudiants[i].name[0], strip(name));
		
		printf("Etudiant %d: Adresse de l'étudiant >", i+1);
		scanf(" %s", &etudiants[i].address[0]);
		
		printf("Etudiant %d: Notes de l'étudiant en ProgC et SysEx >", i+1);
		scanf("%hu %hu", &etudiants[i].marks.ProgC, &etudiants[i].marks.SysEx);
		printf("\n");
	}

	int entrysize = sizeof(struct student) + 2;
	char *content = calloc(tabsize, entrysize);

	for (int i=0; i < tabsize; i++) {
		printf("Name %i: %s",i, etudiants[i].firstname);
		strcat(content, etudiants[i].firstname);
		
		printf("Firstname %i: %s", i, etudiants[i].name);
		strcat(content, etudiants[i].name);
		
		printf("Address %i: %s", i, etudiants[i].address);
		strcat(content, etudiants[i].address);
		
		char progCstr[3];
		sprintf(progCstr, "%d", etudiants[i].marks.ProgC);
		strcat(content, progCstr);
		
		char sysExstr[3];
		sprintf(sysExstr, "%d", etudiants[i].marks.SysEx);
		strcat(content, sysExstr);
		
		if (i != tabsize - 1) {
			strcat(content, ", ");
		}
		printf("Wrote line %i\n", i);
	}
	
	char file[] = "./db_etudiants";
	ecrire_dans_fichier(file, content);
	free(content);
	printf("=========FILE CONTENT=========\n");
	lire_fichier(file);

	return 0;
}
