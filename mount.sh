#!/bin/sh
# This script will run once refreshment is not needed
# FIXME: get rid of compilation
root="${0%/*}"

in="${root}/mount.c"
out="${root}/bin/mount"

echo "Compiling ${in} to ${out}"
sleep 1

clang ${in} -o ${out}
${out}