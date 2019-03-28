@echo off
:: composed by kroko / WARP

set PATH_USER_CALL=%CD%
set PATH_DEP=%~dp0

:: ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Clean up if exists

echo Deleting old directories if exist
rd "%PATH_DEP%glad" /s /q
rd "%PATH_DEP%glfw" /s /q
rd "%PATH_DEP%glfw-3.2.1.bin.WIN32" /s /q
rd "%PATH_DEP%glfw-3.2.1.bin.WIN64" /s /q
rd "%PATH_DEP%tmp" /s /q

:: ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Build GLAD

echo Starting GLAD ...
set PATH_GLAD_GENERATOR=%PATH_DEP%tmp\glad-generator
set PATH_GLAD_OUT=%PATH_DEP%glad
md "%PATH_GLAD_GENERATOR%"
git clone --branch master --single-branch --depth 1 https://github.com/Dav1dde/glad.git "%PATH_GLAD_GENERATOR%"
py "%PATH_GLAD_GENERATOR%\main.py" --out-path="%PATH_GLAD_OUT%" --generator=c --spec=gl --profile=core
rd "%PATH_GLAD_GENERATOR%" /s /q
echo ... GLAD phase ended.

:: ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Build GLFW

echo Starting GLFW ...

set PATH_GLFW_BASE=%PATH_DEP%tmp\glfw
:: not using here, using devenv instead of cmake middleman for actual building, no intallation dir, manual moveout
:: set PATH_GLFW_BUILD=%PATH_DEP%tmp\glfw\build

md "%PATH_GLFW_BASE%"

:: Mirror output directory structure for case when prebuilt MSW libs would be used
set PATH_GLFW_OUT_ALL=%PATH_DEP%glfw
md "%PATH_GLFW_OUT_ALL%\include"

set PATH_GLFW_OUT_X86=%PATH_GLFW_OUT_ALL%\lib-vc2017\x86
md "%PATH_GLFW_OUT_X86%\Debug\static"
md "%PATH_GLFW_OUT_X86%\Debug\dynamic"
md "%PATH_GLFW_OUT_X86%\Release\static"
md "%PATH_GLFW_OUT_X86%\Release\dynamic"

set PATH_GLFW_OUT_X64=%PATH_GLFW_OUT_ALL%\lib-vc2017\x64
md "%PATH_GLFW_OUT_X64%\Debug\static"
md "%PATH_GLFW_OUT_X64%\Debug\dynamic"
md "%PATH_GLFW_OUT_X64%\Release\static"
md "%PATH_GLFW_OUT_X64%\Release\dynamic"

cd "%PATH_GLFW_BASE%"
:: Needs MSW10, because of OOB *Powershell* version (5.0+) that has unzipping built in, let's stick with git
:: powershell -Command "(New-Object Net.WebClient).DownloadFile('https://github.com/glfw/glfw/releases/download/3.2.1/glfw-3.2.1.zip', 'glfw-3.2.1.zip')"
:: powershell -Command "Invoke-WebRequest https://github.com/glfw/glfw/releases/download/3.2.1/glfw-3.2.1.zip -OutFile glfw-3.2.1.zip"
:: powershell Expand-Archive glfw-3.2.1.zip -DestinationPath .

git clone --branch 3.2.1 --single-branch --depth 1 https://github.com/glfw/glfw.git glfw-3.2.1

:: make 32bit version, move out results
:: 32bit static start
echo ... Building 32bit static ...
md makestatic-x86
cd makestatic-x86
cmake -G "Visual Studio 15 2017" -DLIB_SUFFIX="" -DGLFW_BUILD_EXAMPLES=0 -DGLFW_BUILD_TESTS=0 -DGLFW_BUILD_DOCS=0 ..\glfw-3.2.1
:: cmake -E env CMAKE_C_FLAGS_DEBUG="/Z7"
:: devenv GLFW.sln /Build "Debug|x86"
devenv GLFW.sln /build Debug
xcopy src\Debug "%PATH_GLFW_OUT_X86%\Debug\static"
:: devenv GLFW.sln /Build "Release|x86"
devenv GLFW.sln /build Release
xcopy src\Release "%PATH_GLFW_OUT_X86%\Release\static"
cd ..
:: 32bit static end

:: 32bit dylib start
echo ... Building 32bit dylib ...
md makedynamic-x86
cd makedynamic-x86
cmake -G "Visual Studio 15 2017" -DBUILD_SHARED_LIBS=ON -DLIB_SUFFIX="" -DGLFW_BUILD_EXAMPLES=0 -DGLFW_BUILD_TESTS=0 -DGLFW_BUILD_DOCS=0 ..\glfw-3.2.1
:: devenv GLFW.sln /Build "Debug|x86"
devenv GLFW.sln /build Debug
xcopy src\Debug "%PATH_GLFW_OUT_X86%\Debug\dynamic"
:: devenv GLFW.sln /Build "Release|x86"
devenv GLFW.sln /build Release
xcopy src\Release "%PATH_GLFW_OUT_X86%\Release\dynamic"
cd ..
:: 32bit dylib end

:: make 62bit version, move out results
:: 64bit static start
echo ... Building 64bit static ...
md makestatic-x64
cd makestatic-x64
cmake -G "Visual Studio 15 2017 Win64" -DLIB_SUFFIX="" -DGLFW_BUILD_EXAMPLES=0 -DGLFW_BUILD_TESTS=0 -DGLFW_BUILD_DOCS=0 ..\glfw-3.2.1
:: devenv GLFW.sln /Build "Debug|x64"
devenv GLFW.sln /build Debug
xcopy src\Debug "%PATH_GLFW_OUT_X64%\Debug\static"
:: devenv GLFW.sln /Build "Release|x64"
devenv GLFW.sln /build Release
xcopy src\Release "%PATH_GLFW_OUT_X64%\Release\static"
cd ..
:: 64bit static end

:: 64bit dylib start
echo ... Building 64bit dylib ...
md makedynamic-x64
cd makedynamic-x64
cmake -G "Visual Studio 15 2017 Win64" -DBUILD_SHARED_LIBS=ON -DLIB_SUFFIX="" -DGLFW_BUILD_EXAMPLES=0 -DGLFW_BUILD_TESTS=0 -DGLFW_BUILD_DOCS=0 ..\glfw-3.2.1
:: devenv GLFW.sln /Build "Debug|x64"
devenv GLFW.sln /build Debug
xcopy src\Debug "%PATH_GLFW_OUT_X64%\Debug\dynamic"
:: devenv GLFW.sln /Build "Release|x64"
devenv GLFW.sln /build Release
xcopy src\Release "%PATH_GLFW_OUT_X64%\Release\dynamic"
cd ..
:: 64bit dylib end

:: copy headers
xcopy /s/e glfw-3.2.1\include "%PATH_GLFW_OUT_ALL%\include"

cd "%PATH_USER_CALL%"
rd "%PATH_GLFW_BASE%" /s /q

echo ... GLFW phase ended.

:: ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Clean up tmp
rd "%PATH_DEP%tmp" /s /q

:: ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Profit

EXIT /B 0
