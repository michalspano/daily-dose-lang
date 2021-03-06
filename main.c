/* 
 *          DAILY DOSE (of) LANGUAGES - DD(o)L
 *
 *                CS50x - Final Project
 *                         ***
 *               Current version: v0.0.0
 *                    Michal Špano
 *
 *           
 */

// Dependencies
#include "types.h"
#include "colors.h"

// Node struct for linked list
struct node {
    char *data;
    struct node *next;
};

// Define the main function
int main(int argc, char *argv[]) {
                                                                            /*       
        --- Minimum number of command line arguments ---
    [0]. base filename; [1]. database_path; [2]. optional flags             */

    if (argc < 2) {
        sys_abort(USAGE);
    }

                                                                            /*
                --- Getting the root of the project ---
        The file structure can be observed via running ./schema.sh
        This will infer global support from the command line
                                                                            */
    char script_source[MAX_STR_LENGTH];
    strcpy(script_source, argv[0]);
    char *last_slash = strrchr(script_source, '/');
    *last_slash = '\0';
    last_slash = strrchr(script_source, '/');
    *last_slash = '\0';

    // Modify paths to global support with the root folder
    char TRANSLATION[MAX_STR_LENGTH], output_path[MAX_STR_LENGTH];
    snprintf(TRANSLATION, MAX_STR_LENGTH, "%s/%s", script_source, root_translate);
    snprintf(output_path, MAX_STR_LENGTH, "%s/%s", script_source, root_out);

    // Deploy initial function to greet the user

    char *database_path = argv[1];

    // Check empty invoke -> Show usage
    if (strcmp(database_path, "null") == 0) {
        sys_abort(USAGE);
    }

    // Check if IO paths are valid
    else if (!validatePath(database_path)) {
        exit(fileAbort(database_path));
    }
    else if (!validatePath(output_path)) {
        exit(fileAbort(output_path));
    }
    else if (!validatePath(TRANSLATION)) {
        exit(fileAbort(TRANSLATION));
    }

    // Get the language prefix from the desired wordlist
    const char *lang_prefix = languageOptions(database_path);
    if (lang_prefix == NULL) {
        sys_abort(INVALID_LANGUAGE);
    }

    bool enableTimeTracking = true;

    // Initial greet function
    greet();

    // Validate any optional flags
    if (argc == 3) {
        char *flag = argv[2];
        if ((strcmp(flag, "-ul") == 0) || (strcmp(flag, "--unlimited-mode") == 0)) {
            printf("%sUnlimited mode enabled!%s\n", YELLOW, RESET);
            enableTimeTracking = false;
        } else {
            sys_abort(USAGE);
        }
    }

    // Default behavior is to enable time tracking
    if (enableTimeTracking) {
        long d;
        if (!eligibleForRefresh(&d, TRANSLATION)) {
            printf("%sRefresh in: %s%li seconds.%s", RED, ITALICS, (time_gap - d), RESET);
            printf("%s Displaying the last entry. %s\n", RED, RESET);
            sleep(1);

            // Run the mount script to display the last entry
            mountScriptInvoke(script_source);
            return 1;
        }
    }

    // Create new linked list
    struct node *head = NULL;
    struct node *current = NULL;
    int word_count = 0, longest_word = 0;

    // Read from the database
    FILE *database = fopen(database_path, "r");

    // Fixed size buffer for reading from file
    char line[MAX_STR_LENGTH];

    // Insert data into a singly linked list
    while (fgets(line, sizeof(line), database)) {
        // Create a new node
        struct node *new_node = (struct node *) malloc(sizeof(struct node));

        // Change longest word if necessary
        if (strlen(line) > longest_word) {
            longest_word = strlen(line);
        }

        // Skip words starting with a hyphen 
        // Hence 'translate' function takes flags in the form:
        // -s -t -h, etc.
        if (line[0] == '-') {
            continue;
        }

        // Copy the data from the file into the node
        new_node->data = strdup(line);

        // Point the next pointer to NULL
        new_node->next = NULL;

        // If the linked list is empty
        if (head == NULL) {
            head = new_node;
        } else {
            current->next = new_node;
        }

        // Reset current node to new_node
        current = new_node;

        // Increment word count
        word_count++;
    }

    // Free the memory
    fclose(database);

    // Reset the seed
    SEED_RESET;
    int i = 0;
    bool toWriteCurrentWord;

    // The number of desired words will be set to 10
    // This behaviour can be overridden by the user
    const int numberOfDesiredWords = 10;

    // Percentage ratio
    int ratio = word_count / numberOfDesiredWords;

    // Buffer to hold randomly chosen words
    char *arr[numberOfDesiredWords];

    // Iterate through the linked list
    for (struct node *current = head; current != NULL; current = current->next) {
        // Handle the base case
        if (i == numberOfDesiredWords || current->next == NULL) {
            break;
        }

        // Decide upon random event
        // The current module will infer the count to be <0; 10> randomly
        toWriteCurrentWord = computeRandomEvent(ratio);
        if (toWriteCurrentWord) {
            arr[i] = current->data;
            i++;
        }
    }
    // Print the words
    printf("%s%sRandomly chosen words:\n\n%s", GREEN, UNDERLINE, RESET);

    // Create the translation command
    char translate_command[50];
    snprintf(translate_command, sizeof(translate_command), "translate -s %s -t %s", lang_prefix, "en");

    // Open the output file and handle errors
    FILE *output = fopen(output_path, "w");
    if (output == NULL) {
        sys_abort("File error.");
    }

    // Translation output file reset
    FILE *translation_reset = fopen(TRANSLATION, "w");
    if (translation_reset == NULL) {
        sys_abort("File error.");
    }
    fclose(translation_reset);

    // Detect the current time
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // Convert to string 
    char time_string[80];
    strftime(time_string, sizeof(time_string), "%c", &tm);

    // Write to translation_path
    FILE *translationFile = fopen(TRANSLATION, "a");
    fprintf(translationFile, "%s\n", time_string);
    fclose(translationFile);

    // Create the write command, with'>>' 
    char writeCommand[MAX_STR_LENGTH];
    snprintf(writeCommand, sizeof(writeCommand), ">> %s\n", TRANSLATION);

    // Iterate over the contents of the array
    // Exclude garbage values
    for (int j = 0; j < i; j++) {

        // Write word to output file
        fprintf(output, "%s", arr[j]);

        // Create a cmd buffer
        char cmd[256];

        // Remove words' new line character
        char strip_word[strlen(arr[j])];
        strcpy(strip_word, arr[j]);
        strip_word[strlen(arr[j]) - 1] = '\0';

        // Format the command
        snprintf(cmd, sizeof(cmd), "%s '%s' %s", translate_command, strip_word, writeCommand);

        // Print the current chosen word
        printf("%s%s%s", CYAN, arr[j], RESET);
        
        // Execute the command and delay
        system(cmd);
        sleep(API_DELAY);
    }

    // Close the output file
    fclose(output);

    // After successful completion, call the mount script by default
    mountScriptInvoke(script_source);
    return 0;
}

// Create an initial function to greet the user
void greet(void) {
    system("clear"); // Reset the terminal screen

    // Parse current terminal session options 
    int width = termWidth();
    int p_length = strlen(PROMPT);
    int spare_tiles = width - p_length;

    // If no padding is needed, print the prompt
    if (spare_tiles < 0) {
        GREET;
    } else {
        // Add padding to the prompt
        for (int i = 0; i < spare_tiles / 2; i++) {
            printf(" ");
        }
        GREET;
    }

    // Color the line break
    printf("%s", CYAN);

    // Print the line break with adequate padding
    for (int i = 0; i < width / 2; i++) {
        if (i <= width / 4) {
            printf(" ");
            continue;
        }
        else if (i >= (width / 4) * 3) {
            printf(" ");
            continue;
        }
        printf("%s", "* ");
    }

    // Evaluation message
    printf("%s\n\n", RESET);
    sleep(1);
}

// Create a function to abort the program with a message
int sys_abort(char *msg) {
    printf("%s%s%s\n", RED, msg, RESET);
    exit(1);    
}

// Report handle file errors
int fileAbort(char *err_path) {
    printf("%sError opening file %s.%s\n", RED, err_path, RESET);
    return 1;
}

// Evaluate current terminal session
int termWidth(void) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}


// Check if given path exists
bool validatePath(char *path) {
    // Check if the given path exists
    if (access(path, F_OK) != -1) {
        return true;
    }
    // Warn the user
    return false;
}

const char *languageOptions(char *db_path) {
    // Determine the language option from the 'db_path'
    // Example: "./database/german_wordlist.txt" -> "german"
    char *language = malloc(sizeof(char) * strlen(db_path));
    strcpy(language, db_path);
    language = strrchr(language, '/') + 1;
    language = strtok(language, ".");
    language = strtok(language, "_");

    // Return the language option abbreviation
    for (int i = 0; i < SIZE; i++) {
        if (strcmp(language, LANGUAGES[i]) == 0) {
            return LANGUAGES[i + 1];
        }
    }
    return NULL;
}

// Compute random event
bool computeRandomEvent(int p) {
    int r = (rand() % p) < 1;
    switch (r) {
    case 1:
        return true;
    default:
        return false;
    }
}

// Create a function to determine eligible for a refreshent
bool eligibleForRefresh(long* d_p, char *translation_path) {
    time_t T;
    time(&T);
    const char *default_time = readLine(translation_path);

    // If is empty return true -> new activity
    if (default_time == NULL) {
        return true;
    }

    // Convert default_time to type time_t
    struct tm raw_time;
    strptime(default_time, "%a %b %d %H:%M:%S %Y", &raw_time);

    // Convert t to type time_t
    time_t default_time_t = mktime(&raw_time);

    // Convert T to type time_t
    time_t current_time_t = mktime(localtime(&T));

    // Compare two times
    double diff = difftime(current_time_t, default_time_t);

    // Update diff
    *d_p = diff;

    if (diff <= time_gap) {
        return false;
    }
    else {
        return true;
    }
}

// Read from a file
// Used to determine the last refresh time
char *readLine(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        sys_abort("F");
    }
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    read = getline(&line, &len, file);
    // Check if file is empty
    if (read == -1) {
        return NULL;
    }
    // Replace '\n' with an empty string
    line[strlen(line) - 1] = '\0';
    fclose(file);
    return line; 
}

// Mount script invoke
void mountScriptInvoke(char *rootPath) {
    char buffMountCmd[MAX_STR_LENGTH];
    snprintf(buffMountCmd, sizeof(buffMountCmd), "sh %s/mount.sh", rootPath);
    system(buffMountCmd);
}
