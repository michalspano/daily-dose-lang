#!/bin/sh
# This script will run once refreshment is not needed
# FIXME: get rid of compilation
root="${0%/*}"
in="${root}/mount.c"
out="${root}/bin/mount"
${out}