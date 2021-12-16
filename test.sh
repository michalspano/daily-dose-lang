#!/bin/sh
# FIXME: Temporary replacement of run.sh
current_path="$0"
dict_lang="$1"

# Strip to directory only
current_path="${current_path%/*}"
fixied_bin_path="/bin/main"

database_path="${0%/*}/database/"

# Load the name of the files from database_path to an array
files=()

for file in $database_path*; do
    files+=("${file##*/}")
done

for f in "${files[@]}"; do
    # Remove file extension
    f="${f%.*}"
    if [ "$f" = "${dict_lang}" ]; then
        user_langugae_path="${database_path}${f}.txt"
        echo "${user_langugae_path}"
        break
    fi
    user_langugae_path="null"
done

# Concatinate the path and the binary name
bin_path="$current_path$fixied_bin_path"

# Default run
if [ -z "$2" ]; then
    exec "$bin_path" "$user_langugae_path"
else
    # Parse any additional flags
    exec "$bin_path" "$user_langugae_path" "$2"
fi  