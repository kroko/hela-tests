@echo off
:: composed by kroko / WARP

set PROJECT_NAME=HelloFBdev

:: ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: If you don't want to open Viusl Studio - sure, you can build from bat
set PATH_USER_CALL=%CD%
set PATH_SOLUTION_DIR=%~dp0

:: ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Try generating symlinks

call "%PATH_SOLUTION_DIR%%PROJECT_NAME%\generate-symlinks.bat"

:: ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Build

devenv "%PATH_SOLUTION_DIR%%PROJECT_NAME%.sln" /Build "Debug|x86"
devenv "%PATH_SOLUTION_DIR%%PROJECT_NAME%.sln" /Build "Release|x86"
devenv "%PATH_SOLUTION_DIR%%PROJECT_NAME%.sln" /Build "Debug|x64"
devenv "%PATH_SOLUTION_DIR%%PROJECT_NAME%.sln" /Build "Release|x64"

:: ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Profit

EXIT /B 0
