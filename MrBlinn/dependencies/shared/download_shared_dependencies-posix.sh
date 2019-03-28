#!/usr/bin/env bash
# composed by kroko / WARP

# don't use GNU readlink -f as coreutils might not be present
realpath_normalized_abs() {
  [[ $1 = /* ]] && echo "$1" || echo "$PWD/${1#./}"
}

PATH_USER_CALL=$(pwd)
PATH_SCRIPT=$(realpath_normalized_abs $0)
PATH_DEPENDENCIES=$(dirname "$PATH_SCRIPT")

echo "================================"
echo "Downloading Hela and submodules"
rm -rf "${PATH_DEPENDENCIES}/hela"
git clone --recursive --branch master --single-branch --depth 1 --shallow-submodules https://github.com/kroko/hela.git "${PATH_DEPENDENCIES}/hela"

echo "================================"
echo "Downloading GLM"
rm -rf "${PATH_DEPENDENCIES}/glm"
git clone --branch 0.9.9.4 --single-branch --depth 1 https://github.com/g-truc/glm.git "${PATH_DEPENDENCIES}/glm"

echo "================================"
echo "Downloading STB"
rm -rf "${PATH_DEPENDENCIES}/stb"
mkdir -p "${PATH_DEPENDENCIES}/stb"
git clone --branch master --single-branch --depth 1 https://github.com/nothings/stb.git "${PATH_DEPENDENCIES}/stb/stb"

echo "================================"
echo "Done"

exit 0