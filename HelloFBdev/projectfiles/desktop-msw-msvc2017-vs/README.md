# Hello FBdev - devbench MSW MSVC

## Build dependencies

Refer to devbench dependencies readme for this OS and compiler.

## Before opening `<ProjectName>\ProjectName.sln` construct path symlinks

To get `code` and `dependencies` in `$(ProjectDir)` symlinks need to be created to *the real* `code` and `dependencies` few levels higher.

Navigating to `<ProjectName>` directory and double clicking `generate-symlinks.bat` in *File Exploer* should do the trick.

If anything goes wrong then manual creation would be done using *Developer Command Promt* to create symlinks.

```bat
:: cd <ProjectName> :: at this point you should be in same directory as <ProjectName>.vcxproj aka $(ProjectDir)
mklink /d .\code ..\..\..\code
mklink /d .\dependencies ..\..\..\dependencies
```

It enables Visual Studio to see `code` and `dependencies` in *Show All Files* mode and it is easy to *Include In Project* and *Exclude From Project* parts that are needed or irrelevant respectively.

Header and library search paths in project properties does not go through these symlinks, but are relative upwards. Because Microsoft Windows and Visual Studio.

## Building

Open `<ProjectName>.sln` and build.  
Or execute `<ProjectName>.bat` using *Developer Command Promt* (will build all permutations *Debug|x86*, *Release|x86*, *Debug|x64*, *Release|x86* OOB).

## Products

Products are placed in `Build` directory next to `<ProjectName>.sln`.

## Just for reference

#### Include Directories (header search paths)

```
$(ProjectDir)..\..\..\code\include
$(ProjectDir)..\..\..\code\<project_specific>
$(ProjectDir)..\..\..\dependencies\shared\hela\hela\include
$(ProjectDir)..\..\..\dependencies\shared\hela\food\spdlog\include
$(ProjectDir)..\..\..\dependencies\shared\<project_specific>
$(ProjectDir)..\..\..\dependencies\devbenches\msw-msvc\glad\include
$(ProjectDir)..\..\..\dependencies\devbenches\msw-msvc\glfw\include
```

#### Library Directories (lib search paths)

Refer to GLFW file tree using VS macros `...(x86|x64)\(Debug|Release)...`  
Use always static versions.

```
$(ProjectDir)..\..\..\dependencies\devbenches\msw-msvc\glfw\lib-vc2017\$(PlatformShortName)\$(Configuration)\static
```

#### Linker Additional Dependencies

```
opengl32.lib
glfw3.lib
```

#### Output and intermediate

```
$(SolutionDir)Build\$(PlatformShortName)\$(Configuration)\
BuildObj\$(PlatformShortName)\$(Configuration)\
```

#### Post Build event

Copy assets directory from *code* next to the built binary

```
xcopy "$(ProjectDir)..\..\..\code\assets" "$(TargetDir)assets" /D /Y /E /I
```
