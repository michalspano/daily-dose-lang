#include <stdio.h>
#include <stdlib.h>
#include "colors.h"

// Max size of string
#define MAX 256

// Define constant PATHS
const char* input_path = "./dist/output.txt";
const char* translation_path = "./dist/translation.txt";

// Define a struct to hold words and their translations
typedef struct {
    char original_word[MAX];
    char translation[MAX];
} word_t;

int main(void) {
    system("clear"); // Clear terminal session

    // Open the input file and handle errors
    FILE* input_file = fopen(input_path, "r");
    if (input_file == NULL) {
        printf("Error opening input file\n");
        return 1;
    }
    // Open the translation file and handle errors
    FILE* translation_file = fopen(translation_path, "r");
    if (translation_file == NULL) {
        printf("Error opening translation file\n");
        return 1;
    }
    // Print header
    printf("%s%sWords For Today\n%s", YELLOW, UNDERLINE, RESET);

    word_t word;
    int idx = 1;
    // Skip first line in the translation file
    fscanf(translation_file, "%*[^\n]\n");
    // Scan the input file and the translation file
    while (fscanf(input_file, "%s", word.original_word) != EOF) {
        fscanf(translation_file, "%s", word.translation);
        // Print the word and its translation in a formatted way
        printf("%i. %s%s%s%s ~ %s%s%s%s\n", 
        idx, CYAN, BOLD, word.original_word, RESET, 
        GREEN, ITALICS, word.translation, RESET);
        idx++;
    }
    return 0;
}