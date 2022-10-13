#include <stdio.h>
#include <string.h>

struct module {
	short ProgC;
	short SysEx;
};

struct etudiant {
	char name[20];
	char surname[20];
	char address[50];
	struct module grades;
};


int main() {
	
	struct etudiant etudiants[5];
	char inames[5][20] = 	{"Anatole", "Bethesda", "Cerveaux", "Delabie", "Enantio"};
	char isurnames[5][20] = {"François","Gerard","Hector","Iana","Johanna"};
	char iaddresses[5][50] ={"1 rue du Kernel","2 avenue des Lauriers","3 boulevard des Manouches","4 chemin des Narines","5 impasse des Oubliés"};
	short igrades[5][2] = 	{ {20,11}, {19,12}, {18,13}, {17,14}, {16,15} };

	for (short i=0; i<5; i++) {
		strcpy( etudiants[i].name, inames[i] );
		strcpy( etudiants[i].surname, isurnames[i] );
		strcpy( etudiants[i].address, iaddresses[i] );
		etudiants[i].grades.ProgC = igrades[i][0];
		etudiants[i].grades.SysEx = igrades[i][1];
	}

	for (short i=0; i<5; i++) {
		printf("%s %s habitant au %s a eu %hu en Programmation C et %hu en Systèmes d'exploitation\n", 
		etudiants[i].name,
		etudiants[i].surname,
		etudiants[i].address,
		etudiants[i].grades.ProgC,
		etudiants[i].grades.SysEx);
	}

	return 0;
}
