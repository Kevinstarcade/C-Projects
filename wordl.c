#include <stdio.h>
#include <string.h>
const char * const GREEN = "\x1b[32m";
const char * const YELLOW = "\x1b[33m";
const char * const WHITE = "\x1b[0m";
const char * current = WHITE;

void setColour(const char *colour) {
  if (current == colour) return;
  printf("%s", colour);
  current = colour;
}

void wordl(const char *theWord) {
  int size = strlen(theWord);
  int correct;
  int colors[] = {0,0,0,0,0,0,0,0,0,0,0,0};
  colors[size] = -1;


  for (int attempt = 0; attempt < 6; setColour(WHITE), ++attempt){
    correct = 1;
    for (int i = 0; colors[i] != -1; ++i) colors[i] = 0;

    printf("Enter guess: ");
    char guess[12];
    scanf("%s", guess);

    // check guess length
    if (strlen(guess) != size) {
	printf("Invalid guess, guess length must match word length\n");
    	return;
    }

    // check for green
    for (int i = 0; guess[i] != '\0'; ++i) {
	if (guess[i] == theWord[i]) {
	  colors[i] = 1;
	} else correct = 0;
    }

    // check for correct word
    if (correct) {
	setColour(GREEN);
	printf("%s\n", guess);
	setColour(WHITE);
	printf("Finished in %d guesses\n", attempt+1);
	return;
    }

    //check for yellow
    for (int i = 0; theWord[i] != '\0'; ++i){
	for (int j = 0; j < size; ++j) {
	   if (theWord[i] == guess[j] && colors[j] == 0 && colors[i] != 1) {
		colors[j] = 2;
		break;
	   }
	}
    }

    //print colors
    for (int i = 0; i < size; ++i) {
	if (colors[i] == 1) setColour(GREEN);  
	else if (colors[i] == 2) setColour(YELLOW);
	else setColour(WHITE);
	printf("%c", guess[i]);
    }
    printf("\n");
   
  }
  printf("Failed to guess the word: %s\n", theWord);
}


int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: %s word\n", argv[0]);
    return 1;
  }
  // theWord is not a pointer to a string that stores the command line argument word that was provided.
  char *theWord = argv[1];

  wordl(theWord);
}
