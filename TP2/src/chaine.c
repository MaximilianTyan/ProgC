#include <stdio.h>

int len(char *str) {
	int length = 1;
	while(*str != 0) {
		str ++;
		length ++;
	}
	return length;
}

void strcopy(char *str1, char *str2) {
	for (int i=0; i < len(str1); i++) {
		*(str2+i) = *(str1+i);
	}
}

void strconcat(char *str1, char *str2, char *strout) {
	for (int i=0; i < len(str1)-1; i++) {
		*(strout + i) = *(str1 + i);
	}
	for (int j=0; j< len(str2); j++) {
		*(strout + len(str1)-1 + j) = *(str2 + j);
	}

}

int main() {
	char str[] = "chaine";
	printf("Str1: %s : %d\n", str, len(str));
	
	char str2[len(str)];
	strcopy(str, str2);
	printf("Str2 (copie) : %s\n", str2);
	
	char str3[len(str) + len(str2) - 1];
	strconcat(str, str2, str3);
	printf("Str3 (concaténation) : %s\n", str3);
	
	return 0;
}
