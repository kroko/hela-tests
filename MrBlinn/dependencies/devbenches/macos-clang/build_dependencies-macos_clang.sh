#!/usr/bin/env bash
# composed by kroko / WARP

echo 🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠
echo -e "\033[103m"
echo -e "\033[34m"
echo "Build dependencies for the only OS from big-three which essentially does not support open standard, cross platform API for graphics programming and compute. Just a friendly reminder ^_^!"
echo "This will"
echo "- download GLAD from git master, generate code (forcing core profile and gl only)."
echo "- download GLFW source for latest release 3.2.1 and build DYLIBS for that."
echo "Requires:"
echo "- git"
echo "- python"
echo "- CMake"
echo -e "\033[0m"
echo -e "\033[49m"
read -p "Press enter to acknowledge and continue..."

if [[ "$OSTYPE" != "darwin"* ]]; then
  echo ❌❌❌❌❌❌❌❌
  echo "You are not on darwin. Aborting."
  exit 1
fi
 
command -v cmake >/dev/null 2>&1 || {
  echo ❌❌❌❌❌❌❌❌
  echo >&2 "Building GLFW by not using CMake is unnecessary hurdle. Do \"brew install cmake\". Aborting."
  exit 1
}

# don't use GNU readlink -f as coreutils might not be present
realpath_normalized_abs() {
  [[ $1 = /* ]] && echo "$1" || echo "$PWD/${1#./}"
}

PATH_USER_CALL=$(pwd)
PATH_SCRIPT=$(realpath_normalized_abs $0)
PATH_DEP=$(dirname "$PATH_SCRIPT")

# Just clean up previous stuff if exists
rm -rf "$PATH_DEP/glad"
rm -rf "$PATH_DEP/glfw"
rm -rf "$PATH_DEP/tmp"

# ################################################################
# Build GLAD

# echo 🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷

echo "Starting GLAD ..."
PATH_GLAD_GENERATOR=$PATH_DEP/tmp/glad-generator
PATH_GLAD_OUT=$PATH_DEP/glad/
mkdir -p "$PATH_GLAD_GENERATOR"
git clone --branch master --single-branch --depth 1 https://github.com/Dav1dde/glad.git "$PATH_GLAD_GENERATOR"
cd $PATH_GLAD_GENERATOR
python -m glad --out-path="$PATH_GLAD_OUT" --generator=c --spec=gl --profile=core
cd -
rm -rf "$PATH_GLAD_GENERATOR"
echo "... GLAD phase ended."

# ################################################################
# Build GLFW

echo 🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷🔶🔷
echo "Starting GLFW ..."

PATH_GLFW_BASE=$PATH_DEP/tmp/glfw
PATH_GLFW_OUT_X64=$PATH_DEP/glfw/x64
mkdir -p "$PATH_GLFW_BASE"
mkdir -p "$PATH_GLFW_OUT_X64"

PATH_GLFW_INSTALL_DEBUG=$PATH_GLFW_BASE/install/debug
PATH_GLFW_INSTALL_RELEASE=$PATH_GLFW_BASE/install/release

git clone --branch 3.2.1 --single-branch --depth 1 https://github.com/glfw/glfw.git "$PATH_GLFW_BASE/glfw-3.2.1"

mkdir -p "$PATH_GLFW_BASE/makedynamic-x86/Debug" && cd "$_"
cmake -DBUILD_SHARED_LIBS=ON -DGLFW_BUILD_EXAMPLES=0 -DGLFW_BUILD_TESTS=0 -DGLFW_BUILD_DOCS=0 -DCMAKE_INSTALL_PREFIX="$PATH_GLFW_INSTALL_DEBUG" "$PATH_GLFW_BASE/glfw-3.2.1"
cmake --build . --config Debug # call cmake instead of make here
make install
# clean out cmake stuff
rm -rf "$PATH_GLFW_INSTALL_DEBUG/lib/cmake"
rm -rf "$PATH_GLFW_INSTALL_DEBUG/lib/pkgconfig"
# manipulate dynamic lib, assuming dylib placement is in project bundle's Framework directory (ProjectName.app/Contents/Frameworks)
install_name_tool -id "@executable_path/../Frameworks/libglfw.3.2.dylib" "$PATH_GLFW_INSTALL_DEBUG/lib/libglfw.3.2.dylib"
mv "$PATH_GLFW_INSTALL_DEBUG/lib" "$PATH_GLFW_OUT_X64/Debug"

mkdir -p "$PATH_GLFW_BASE/makedynamic-x86/Release" && cd "$_"
cmake -DBUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX="$PATH_GLFW_INSTALL_RELEASE" "$PATH_GLFW_BASE/glfw-3.2.1"
cmake --build . --config Release # call cmake instead of make here
make install
# clean out cmake stuff
rm -rf "$PATH_GLFW_INSTALL_RELEASE/lib/cmake"
rm -rf "$PATH_GLFW_INSTALL_RELEASE/lib/pkgconfig"
# manipulate dynamic lib, assuming dylib placement is in project bundle's Framework directory (ProjectName.app/Contents/Frameworks)
install_name_tool -id "@executable_path/../Frameworks/libglfw.3.2.dylib" "$PATH_GLFW_INSTALL_RELEASE/lib/libglfw.3.2.dylib"
mv "$PATH_GLFW_INSTALL_RELEASE/lib" "$PATH_GLFW_OUT_X64/Release"

# copy headers
cp -pr "$PATH_GLFW_BASE/glfw-3.2.1/include" "$PATH_DEP/glfw"

cd "$PATH_USER_CALL"
rm -rf "$PATH_GLFW_BASE"
echo "... GLFW phase ended."

# ----

rm -rf "$PATH_DEP/tmp"

echo 🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠🧠

exit 0
