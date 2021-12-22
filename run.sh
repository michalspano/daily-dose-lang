#!/bin/sh
# Dump command-line variables
current_path="$0"
dict_wordlist_path="$1"

# fix paths
# run ./schema to view the file structure
current_path="${current_path%/*}"
fixed_bin_path="/bin/main"
database_path="${0%/*}/database/"

# Default var to store the language path
user_language_path=""

# Append 'null' literal if empty path was 
if [ -z "${dict_wordlist_path}" ]; then
    user_language_path="null"

# Overrding the dafault behaviour
# run ./dict_list o view the keys of wordlists
# run ./dict_list --help for further understanding
else
    files=()
    for file in $database_path*; do
        files+=("${file##*/}")
    done
    for f in "${files[@]}"; do
        f="${f%.*}"  # Remove the file extension, voiding '.md' extension
        if [ "$f" = "${dict_wordlist_path}" ]; then
            # This infers the path of the language
            # Break from the loop and append the relative path of the keyword
            user_language_path="${database_path}${f}.txt"
            break
        fi
    done
fi

# Default behaviour - accept the full path
if [ -z "${user_language_path}" ]; then
    user_language_path="${dict_wordlist_path}"
fi

# Concatinate the path and the binary name
bin_path="$current_path$fixed_bin_path"

# Default run
if [ -z "$2" ]; then
    exec "$bin_path" "$user_language_path"
# Run with [optional] flgs
else
    exec "$bin_path" "$user_language_path" "$2"
fi  