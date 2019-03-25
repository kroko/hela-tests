#!/usr/bin/env bash

# created as shortcut to ./run.sh with env and arguments populated

realpath_normalized_abs() {
  [[ $1 = /* ]] && echo "$1" || echo "$PWD/${1#./}"
}
PATH_SCRIPT_FILE=$(realpath_normalized_abs $0)
PATH_SCRIPT_DIR=$(dirname $PATH_SCRIPT_FILE)

bash ${PATH_SCRIPT_DIR}/run.sh --width 1920 --height 1080
# GL_KEYBOARD=/dev/input/event1 GL_MOUSE=/dev/input/event0 bash ${PATH_SCRIPT_DIR}/run.sh --width 1920 --height 1080
# GL_KEYBOARD=/dev/input/event1 GL_MOUSE=/dev/input/event0 bash ${PATH_SCRIPT_DIR}/run.sh --width 1280 --height 720
