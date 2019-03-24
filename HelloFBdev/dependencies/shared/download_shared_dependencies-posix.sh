#!/usr/bin/env bash
# composed by kroko / WARP

# don't use GNU readlink -f as coreutils might not be present
realpath_normalized_abs() {
  [[ $1 = /* ]] && echo "$1" || echo "$PWD/${1#./}"
}

PATH_USER_CALL=$(pwd)
PATH_SCRIPT=$(realpath_normalized_abs $0)
PATH_DEPENDENCIES=$(dirname "$PATH_SCRIPT")

echo "Downloading Hela and submodules"
rm -rf "${PATH_DEPENDENCIES}/hela"
git clone --recursive --branch master --single-branch --depth 1 --shallow-submodules https://github.com/kroko/hela.git "${PATH_DEPENDENCIES}/hela"

echo "Done"

exit 0