// Jake Lunski
// CPSC 1071-002
// Binary Beasts
// 4/22/2023

#ifndef QUIDDLERX_H
#define QUIDDLERX_H

// Reads in the dictionary file /usr/share/dict/words and returns the number words that
// have an equal or less than number of characters of maxLength.
int loadDictionary(char *words[], int maxLength);

// Prompts the user to enter in the Quiddler hand as requested in the sample output and returns the
// provided characters with spaces, exactly as typed
char *promptUser();

// Calculates and returns the point value of a single or two-letter card based on the Quiddler scoring chart.
int getLetterPoints(const char *str);

//  Calculates the total points of a word formed using the cards.
int wordPoints(char *word, char **cards, int numCards, int wordLength);

// Prints the matched words along with their point values.
void printResults(char *words[], int length, char **cards, int cardsLength);

// Splits the pointer to a string nto an array of strings based on spaces.
// Calls the loadDictionary function after determining what the maximum word length will be
// Calls the printResults function after the list of viable words has been formed
void processGuess(char *cardString);

// I added this function to find all valid words that can be formed from the given cards. It uses recursion to try different 
// combinations of cards to form new words and then checks if the new words are found in the dictionary. It has the following parameters:
void findMatchingWords(char *cards[], int cardCount, int used[], char *currentWord, int currentLength, char **dictionary, int numWords, char **matchedWords, int *matchedCount, int *matchedWordIndices);

// Starts the process of the Quiddler assistant. This should be the only function call in your provided
// main method and should handle all expected functionality.
void helpMe();


#endif
