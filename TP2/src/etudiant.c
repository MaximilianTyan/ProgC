#include <stdio.h>
#include <string.h>

int main() {
	
	char inames[5][20] = 	{"Anatole", "Bethesda", "Cerveaux", "Delabie", "Enantio"};
	char isurnames[5][20] = {"François","Gerard","Hector","Iana","Johanna"};
	char iaddresses[5][50] ={"1 rue du Kernel","2 avenue des Lauriers","3 boulevard des Manouches","4 chemin des Narines","5 impasse des Oubliés"};
	char igrades[5][2] = 	{ {20,11}, {19,12}, {18,13}, {17,14}, {16,15} };
	
	for (short i=0; i<5; i++) {
		printf("%s %s habitant au %s a eu %hu en Programmation C et %hu en Systèmes d'exploitation\n", 
		inames[i],
		isurnames[i],
		iaddresses[i],
		igrades[i][0],
		igrades[i][1]);
	}

	return 0;
}
