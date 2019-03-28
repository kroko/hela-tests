@echo off
:: composed by kroko / WARP

set PATH_DEPENDENCIES=%~dp0
echo This script assumes you have intsalled git with option to be reachable from MSW built in promts not only Git Bash. Developer Command Promt encouraged.

echo ================================
echo Downloading Hela and submodules
rd "%PATH_DEPENDENCIES%hela" /s /q
git clone --recursive --branch master --single-branch --depth 1 --shallow-submodules https://github.com/kroko/hela.git "%PATH_DEPENDENCIES%hela"

echo ================================
echo Downloading GLM
rd "%PATH_DEPENDENCIES%glm" /s /q
git clone --branch 0.9.9.4 --single-branch --depth 1 https://github.com/g-truc/glm.git "%PATH_DEPENDENCIES%glm"

echo ================================
echo Downloading STB
rd "%PATH_DEPENDENCIES%stb" /s /q
md "%PATH_DEPENDENCIES%stb"
git clone --branch master --single-branch --depth 1 https://github.com/nothings/stb.git "%PATH_DEPENDENCIES%stb\stb"

echo ================================
echo Done