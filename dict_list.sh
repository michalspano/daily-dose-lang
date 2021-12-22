#!/bin/sh
# Script to show all supported dictionaries
database_path="${0%/*}/database/"
flag="$1"

# Help flag
# No flag represents the default behaviour
if [ "$flag" = "-h" ] || [ "$flag" = "--help" ]; then
    printf "Usage: dict_list.sh [OPTION]\n"
    printf "Database path: %s\n" "'$database_path'"
    printf "Options:\n"
    printf "  -h, --help    Show this help message and exit\n"
    printf "  -f, --full    Show relative paths of supposted dictionaries\n"
    printf "                Default: Show only dictionary name\n"
    exit 0
fi

# Colors
RED="\033[0;31m"
GREEN="\033[0;32m"
YELLOW="\033[0;33m"
UNDERLINE="\033[4m"
RESET="\033[0m"

# Print the header
printf "\n${GREEN}${UNDERLINE}Supported dictionaries - "

# Check if the flag is set to '-f' or '--full'
if [ "$flag" = "-f" ] || [ "$flag" = "--full" ]; then
    printf "(relative path):${RESET}\n"
    ifFull=1
else
    printf "(key flags):${RESET}\n"
    ifFull=0
fi    

# Format the output
function format_output() {
    printf "${YELLOW}${1}\n${RESET}"
}

# Iterate over all parsed files from the dir
for file in $database_path*; do
    filename=$(basename "$file")
    # Detect the file extension
    extension="${filename##*.}"
    if [ "$extension" = "txt" ]; then
        if [ $ifFull -eq 1 ]; then
            format_output "${file}"
        else
            format_output "${filename%.*}"
        fi
    fi
done
exit 0
