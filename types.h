// Include standard library dependencies
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

// Define MACROS
#define USAGE "Usage: ./main.c <database_input>\nOptional flags:\n-ul, --unlimited  Unlimited mode (disabled real-time counter)\n"
#define GREET printf("%s%s%s\n", GREEN, PROMPT, RESET)
#define MAX_STR_LENGTH 256
#define SEED_RESET srand(time(NULL))
#define INVALID_LANGUAGE "Invalid language."
#define API_DELAY 1

// Global constants
const long time_gap = 43200;
static char *root_translate = "dist/translation.txt";
static char *root_out = "dist/output.txt";
const char *PROMPT = "Welcome to your Daily Dose of Languages!";

// Possible languages options (statically defined)
const int SIZE = 6;
const char* LANGUAGES[SIZE] = {"german", "de",
                                "russian", "ru",
                                "swedish", "sv"
};

// Function prototypes
void greet(void);
int termWidth(void);
int sys_abort(char *msg);
int fileAbort(char *err_path);
bool computeRandomEvent(int p);
char *readLine(const char *file_path);
const char *languageOptions(char *db_path);
bool validatePath(char *database_path);
bool eligibleForRefresh(long* d_p, char *translation_path);