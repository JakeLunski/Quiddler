// Jake Lunski
// CPSC 1071-002
// Binary Beasts
// 4/22/2023

/*
        Sources
fgets(): C-Strings slides (11)
-  Reads one line of characters from user input ending with a newline and
   writes it to the C-string str, including spaces and tabs.
- I use this int the loadDictionary() and promptUser() functions to get the hand and the size of the hand

strcspn(): Cplusplus.com 
Cplusplus.com. n.d. "strcspn - C++ Reference." Accessed April 22, 2023. 
https://cplusplus.com/reference/cstring/strcspn/?kw=strcspn

- This can be used to search through a string and look for a specific character
- In this case, I use it in the loadDictionary() and promptUser() functions to find the new line character at the end of hand so I can 
  remove the newline character
- I searched how to remove a newline character at the end of a string and something on stack overflow
  came up, it saidf I could use strcspn, so I went to Cplusplus.com to see how it worked, then implemented
  it in my code.
- I also use the in the loadDictionary() function to remove the null char from the buffer string

strlen(): C-String slides (10)
- Returns # of chars up to but not including 1st \0.
- I use this in alot of my functions to comapre words to the string length
- I use this in the loadDictionary() function to check if the word is shorter than the maxlength while searching through the dictionary
- I use this in the printResults() function to make sure the words printed are greater than 2 characters long
- I use it in the processGuess() function to allocate memory the length of the string for possible words

fopen()/fclose(): Cplusplus.com 
Cplusplus.com. n.d. "fopen - C++ Reference." Accessed April 22, 2023. 
https://cplusplus.com/reference/cstdio/fopen/?kw=fopen

- Opens the file whose name is specified in the parameter filename and associates it with a 
  stream that can be identified in future operations by the FILE pointer returned.
- I found this when searching up how to open a file in C. The fopen() function came up so I 
  went to Cplusplus and learned how to use it. I also found out to put it in read mode using 'r'.
- I use this in my loadDictionary() function to load the dictionary.
- Close the file stream when done

malloc(): Linked-Lists-C slides (3, 4)
- Function malloc takes as an argument the number of bytes to be allocated And returns
  a pointer of type void * (pointer to void) to the allocated memory
- I use this in multiple functions in my program
- In the loadDictionary() function i use it to allocate memeory for dictionary words that I remove non-alpha characters from
- In promptUser() to allocate memory for the input
- In findMatchingWords() to allocate memory for the matched word and copy it to the matchedWords array
- In processGuess() to allocate memory for the card and convert it to lowercase

strcpy(): C-String slides (8, 9)
- <string.h> gives a method called strcpy (str1, str2) which copies each character of str2 
  into the memory locations of str1
- str1 must be at least as large as str2 or else runtime error
- I use strcpy()in my loadDictionary() to copy the strippedWord string into the words array.
- In findMatchingWords() to copy the matched words in the dictionary
- In processGuess() to copy the cards array

isAplha(): C-String slides and Cplusplus.com 
Cplusplus.com. n.d. "isalpha - C++ Reference." Accessed April 22, 2023. 
https://cplusplus.com/reference/cctype/isalpha/?kw=isAlpha

- Reference for the <ctype.h> header.
- Checks whether c is an alphabetic letter.
- I use this to check if the character is aplhabetic when searching through the dictioanry. I needed this to filter out non-alpha characters from the dictionary
  so i could search through it accurately.
- I searched up how to check for aplhabetic characters and Cpluplus isAplha() came up, so I implemented it in my program.
- I only use it in the loadDictionary() function to check for alphabetic characters.

strcat(): C-String slides
- #include <string.h> library
- Appends a copy of the source string to the destination string. 
- I use this in my findMatchingWords() function to concatenate the string cards[i] to the end of the string newWord.

strtok(): Cplusplus.com 
Cplusplus.com. n.d. "strtok - C++ Reference." Accessed April 22, 2023. 
https://cplusplus.com/reference/cstring/strtok/?kw=strtok

- I found this function when trying to see if words can be formed compared to the dictionary using the cards.
  I tokenized the string to check one card at a time when comparing.
- I use this in my findMatchingWords() function. I use strtok to tokenize the input cardString into individual cards, separated by spaces.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Quiddler.h"

#define MAX_LENGTH 102401

// This function loads dictionary words into an array of strings, filtering out words that are longer than the maxLength.
int loadDictionary(char *words[], int maxLength) {
    // Open the dictionary file
    FILE *file = fopen("/usr/share/dict/words", "r");
    
    // Check if the file is opened successfully
    if (file == NULL) {
        printf("Error: could not open dictionary file\n");
        return -1;
    }

    char word[MAX_LENGTH];      // declares array of characters with length of MAX_LENGTH 
    int count = 0;              // keeps track of words loaded into words array
    int totalWords = 0;         // keeps track of total words in dictionary

    // Read words from the file into words array
    while (fgets(word, MAX_LENGTH, file) != NULL) {
        word[strcspn(word, "\n")] = 0; // remove newline character

        // Check if the word is shorter than the maxLength
        if (strlen(word) <= maxLength) {

            // Remove all non-alphabetic and non-apostrophe characters, I also have a check for ASCII characters greater than 127
            char strippedWord[MAX_LENGTH];
            int j = 0;
            for (int i = 0; i < strlen(word); i++) {
                if (isalpha(word[i]) || word[i] == '\'' || (unsigned char)word[i] >= 127) {
                    strippedWord[j++] = word[i];
                }
            }
            strippedWord[j] = '\0';     // Add null character to the end of the string
            
            // Check if the stripped word is not empty
            if (strlen(strippedWord) > 0) {
                words[count] = (char*) malloc(strlen(strippedWord) + 1);    // This line allocates memory for the strippedWord string in the words array using malloc.
                strcpy(words[count], strippedWord);                         // Copies the strippedWord string into the words array.
                count++;    
            }
        }
        totalWords++;
    }
    // Close the file and output then return the count
    fclose(file);
    printf("Processing Dictionary\n");
    printf("%d out of %d words in the dictionary are less than %d!\n", count, totalWords, maxLength);
    return count;
}

// This function prints the valid word results from the list of matched words.
void printResults(char *words[], int length) {
    for (int i = 0; i < length; i++) {

        // Check if the length of the word is greater than 2
        if (strlen(words[i]) > 2) {
            printf("\t%d: %s\n", i, words[i]);    // Print out the word index and the word 
        }
    }
}

// Prompts the user for input and returns the input string.
char *promptUser() {
    printf("Welcome to the Quiddler Assistant!\n");
    printf("\n");
    printf("Enter your Quiddler cards with the following scheme:\n");
    printf("    Separate each card with a space\n");
    printf("    Enter cards in any order\n");
    printf("    Example input: 'CL E N A T'\n");
    printf("    Cards: ");
    char *input = malloc(MAX_LENGTH);       // Allocate memory for the input string
    fgets(input, MAX_LENGTH, stdin);        // Get user input using fgets
    input[strcspn(input, "\n")] = '\0';     // Remove newline character from input
    return input;                           
}

// This is a recursive function that tries different combinations of cards to find words that match the dictionary.
void findMatchingWords(char *cards[], int cardCount, int used[], char *currentWord, int currentLength, char **dictionary, int numWords, char **matchedWords, int *matchedCount, int *matchedWordIndices) {
    // Check if the current word has a length greater than 2, and search for it in the dictionary
    if (currentLength > 2) {
        for (int i = 0; i < numWords; i++) {

            // Compare the current word with a dictionary word
            if (strcasecmp(currentWord, dictionary[i]) == 0) {
                matchedWords[*matchedCount] = malloc(strlen(dictionary[i]) + 1);    // Allocate memory for the matched word and copy it to the matchedWords array
                strcpy(matchedWords[*matchedCount], dictionary[i]);
                matchedWordIndices[*matchedCount] = i;             // Save the index of the matched word
                (*matchedCount)++;
                break;
            }
        }
    }

    // Iterate through the cards
    for (int i = 0; i < cardCount; i++) {

        // If the current card has not been used then mark the card as used
        if (!used[i]) {
            used[i] = 1;        
            
            // Create a new word by adding the current card to the current word
            char newWord[MAX_LENGTH * 2];
            strcpy(newWord, currentWord);
            strcat(newWord, cards[i]);

            // Add the current card to the list of matched cards for the new word
            int matchedIndices[MAX_LENGTH];
            int matchedIndexCount = 0;

            // Iterate through the matched words
            for (int j = 0; j < *matchedCount; j++) {

                // If the matched word index is valid and the current card is part of the matched word
                if (matchedWordIndices[j] >= 0 && !strcasecmp(cards[i], dictionary[matchedWordIndices[j]])) {
                    matchedIndices[matchedIndexCount] = j;      // Save the index of the matched word
                    matchedIndexCount++;
                }
            }

            // Recursive function to find matching words
            findMatchingWords(cards, cardCount, used, newWord, currentLength + strlen(cards[i]), dictionary, numWords, matchedWords, matchedCount, matchedWordIndices);

            // Remove the current card from the list of matched cards for the new word
            for (int j = 0; j < matchedIndexCount; j++) {
                matchedWordIndices[matchedIndices[j]] = -1;
            }

            // Mark the card as unused
            used[i] = 0;
        }
    }
}

// This function processes the input string containing the cards and finds the matching words.
void processGuess(char *cardString) {

    // Initialize cards and cardCount
    char *cards[MAX_LENGTH];
    int cardCount = 0;

    // Tokenize the input string to extract cards
    char *word = strtok(cardString, " ");
    while (word != NULL && cardCount < MAX_LENGTH) {
        cards[cardCount] = malloc(strlen(word) + 1);      // Allocate memory for the card and convert it to lowercase
        for (int i = 0; i < strlen(word); i++) {
            word[i] = tolower(word[i]);
        }

        // Copy the card to the cards array
        strcpy(cards[cardCount], word);
        cardCount++;
        word = strtok(NULL, " ");       // Get the next card
    }

    // Calculate the max length of the combined cards
    int maxWordLength = 0;
    for (int i = 0; i < cardCount; i++) {
        maxWordLength += strlen(cards[i]);
    }

    // Load the dictionary and find possible words
    char *possibleWords[MAX_LENGTH];
    int numWords = loadDictionary(possibleWords, maxWordLength);
    if (numWords < 0) {
        printf("Error: could not load dictionary\n");
        return;
    }

    // Initialize matchedWords array and matchedCount
    char *matchedWords[MAX_LENGTH];
    int matchedCount = 0;

    // Initialize array to keep track of the used cards
    int used[MAX_LENGTH] = {0};

    // Initialize currentWord and matchedWordIndices
    char currentWord[MAX_LENGTH] = "";
    int matchedWordIndices[MAX_LENGTH];

    // Call the findMatchingWords function to find the matching words
    findMatchingWords(cards, cardCount, used, currentWord, 0, possibleWords, numWords, matchedWords, &matchedCount, matchedWordIndices);

    // Sort the matched words based on the indices
    for (int i = 0; i < matchedCount - 1; i++) {
        for (int j = i + 1; j < matchedCount; j++) {
            if (matchedWordIndices[i] > matchedWordIndices[j]) {
                // Swap the words
                char *temp = matchedWords[i];
                matchedWords[i] = matchedWords[j];
                matchedWords[j] = temp;

                // Swap the indices
                int tempIndex = matchedWordIndices[i];
                matchedWordIndices[i] = matchedWordIndices[j];
                matchedWordIndices[j] = tempIndex;
            }
        }
    }

    // Print out the matched words
    printf("Possible Options:\n");
    printResults(matchedWords, matchedCount);

    // Free memory
    for (int i = 0; i < numWords; i++) {
        free(possibleWords[i]);
    }
    for (int i = 0; i < matchedCount; i++) {
        free(matchedWords[i]);
    }
    for (int i = 0; i < cardCount; i++) {
        free(cards[i]);
    }
}


// This is the function Main calls that starts the program.
void helpMe() {
    char *hand = promptUser();
    processGuess(hand);
    free(hand);
}