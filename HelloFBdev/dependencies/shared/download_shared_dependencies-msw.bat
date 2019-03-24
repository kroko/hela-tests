@echo off
:: composed by kroko / WARP

set PATH_DEPENDENCIES=%~dp0
echo This script assumes you have intsalled git with option to be reachable from MSW built in promts not only Git Bash. Developer Command Promt encouraged.

echo Downloading Hela and submodules
rd "%PATH_DEPENDENCIES%hela" /s /q
git clone --recursive --branch master --single-branch --depth 1 --shallow-submodules https://github.com/kroko/hela.git "%PATH_DEPENDENCIES%hela"

echo Done