@echo off
:: composed by kroko / WARP

set PATH_PROJECT_DIR=%~dp0

:: ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Generate symlinks

mklink /d "%PATH_PROJECT_DIR%code" ..\..\..\code
mklink /d "%PATH_PROJECT_DIR%dependencies" ..\..\..\dependencies

:: ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Profit

EXIT /B 0
