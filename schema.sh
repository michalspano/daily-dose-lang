#!/bin/sh
# Load the schema of the project
# Loading from a txt_file

# Get to the root directory
# That is the directory of the script
# This is the path to the project
root="${0%/*}"
schema_src="${root}/docs/schema.txt"

while read line; do
    # Ignore lines that start with #
    if [ "${line:0:1}" = "#" ]; then
        continue
    fi
    echo "$line"
done < "$schema_src"