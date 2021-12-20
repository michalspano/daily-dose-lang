#include <stdio.h>
#include <stdlib.h>
#include "colors.h"
#include <strings.h>

// Max size of string
#define MAX 256

// Define constant PATHS
const char* root_out = "/dist/output.txt";
const char* root_translate = "/dist/translation.txt";

// Define a struct to hold words and their translations
typedef struct {
    char original_word[MAX];
    char translation[MAX];
} word_t;

int main(int argc, char* argv[]) {
    system("clear");
                                                                            /* 
            *Global invoke support*
    Let script_source be the root of the project
    The file structure can be observed via running ./schema.sh              */

    char script_source[MAX];
    strcpy(script_source, argv[0]);
    char *last_slash = strrchr(script_source, '/');
    *last_slash = '\0';
    last_slash = strrchr(script_source, '/');
    *last_slash = '\0';

    // Modify paths to global support with the root folder
    char input_path[MAX], translation_path[MAX];
    snprintf(translation_path, MAX, "%s/%s", script_source, root_translate);
    snprintf(input_path, MAX, "%s/%s", script_source, root_out);

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
    // Some words can be separeted with a space
    // A new word is indicated with a new line only!
    // Using an escape character to avoid this
    while (fscanf(input_file, "%[^\n]\n", word.original_word) != EOF) {
        fscanf(translation_file, "%[^\n]\n", word.translation);

        // Print the word and its translation in a formatted way
        printf("%i. %s%s%s%s ~ %s%s%s%s\n",
                idx, CYAN, BOLD, word.original_word, RESET, 
                GREEN, ITALICS, word.translation, RESET
        );
        idx++;
    }
    return 0;
}