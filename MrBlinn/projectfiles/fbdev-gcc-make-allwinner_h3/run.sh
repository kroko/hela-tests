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

run() {
  echo "" &>$PATH_SCRIPT_DIR/run.log
  $PATH_SCRIPT_DIR/$BINARYNAME $@ &>>$PATH_SCRIPT_DIR/run.log
}

init() {
  stty -echo
  tput smcup
  tput civis
  tput clear
  trap cleanup HUP TERM
}

cleanup() {
  read -t 0.001 && cat </dev/stdin >/dev/null
  tput reset
  tput rmcup
  tput cnorm
  stty echo
  clear
  cat $PATH_SCRIPT_DIR/run.log
  exit 0
}

main() {
  tput -T "$TERM" sgr0 >/dev/null || return $?
  init
  run $@
  cleanup
}

main $@
