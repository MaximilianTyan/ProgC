#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/*
int check(char *sentence, char *word) {
	if ( *word == '\0' ) { 
		// If word comparison ended (no more chars to match
		// meaning the comparison ended successfully)
		return 1;
	}
	else if ( *sentence == '\0') {
		// Ran out of chars in sentence to compare
		// Word is too long for the remaining sentence
		// to match
		return 0;
	}
	else if ( *sentence != *word ) {
		// If any character is different, comparison fails
		return 0; 
	}
	else {
		// If the current character is the same as the current
		// comparison, proceed further into the comparison
			return check( sentence+1, word+1 );
	}
}
*/

int main(int argc, char **argv) {

	if (argc != 3) {
		printf("Please enter a word to search and a file where to search it\n");
		printf("According to the syntax: \n$ a.out 'word' 'filepath'\n");
		return 1;
	}
	printf("Searching word '%s' in file %s\n", argv[1], argv[2]);

	int matchcount = 0;
	int charcount = 1;
	int line = 1;

	int commonchars = 0;
	char chr;

	int file = open(argv[2], O_RDONLY);
	
	printf("Match found at\n");
	while (read(file, &chr, 1)) {
		charcount ++;
		
		// Reset cursor position at every newline char
		if (chr == '\n') {
			line++;
			charcount = 1;
			//printf("New line: %i\n",line);
		}
		
		if (chr == argv[1][commonchars]) {
			commonchars++;
			
			// if entierity of the word is matched
			if (commonchars == (int) strlen(argv[1])) {
				printf("char %d at line %d\n", charcount, line);
				matchcount++;
				commonchars = 0;
			}
		}
		else {
			commonchars = 0;
		}	
	}
	
	close(file);
	
	printf("Total number of matches: %d\n", matchcount);

	return 0;
}
