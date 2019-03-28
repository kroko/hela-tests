#!/usr/bin/env bash

# you probably should not run raw binary, but wrap it within tput
# this script does that as well as sets up echoing to run.log file

BINARYNAME=gl-test

# -----------------------------------
realpath_normalized_abs() {
  [[ $1 == /* ]] && echo "$1" || echo "$PWD/${1#./}"
}

PATH_SCRIPT_FILE=$(realpath_normalized_abs $0)
PATH_SCRIPT_DIR=$(dirname "$PATH_SCRIPT_FILE")

echo "" &>$PATH_SCRIPT_DIR/run.log
$PATH_SCRIPT_DIR/$BINARYNAME $@ &>>$PATH_SCRIPT_DIR/run.log
clear
cat $PATH_SCRIPT_DIR/run.log
