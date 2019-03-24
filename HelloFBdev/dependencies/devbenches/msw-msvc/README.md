
# Devbench dependencies MSW MSVC

## Prequisites

Remember not putting this project somewhere deep in your file tree as paths cannot be longer than ~2^8 (max was 260(?), anyways...) on this OS. Still Microsoft Windows. Still waters run deep. Still D.R.E.

This assumes that you have
* *Developer Command Promt* which supposedly is obtainable by enabling *C++/CLI support*
* *Cmake* which is obtainable in multiple ways, but tested by enabling *Visual C++ tools for CMake*
* *Python* which is obtainable in multiple ways, but tested by enabling *Python development* (gives Python 3)
* Git installed with option to be reachable from *Command Promt* and *PowersShell* (not *Git Bash only*) which also makes it reachable in *Developer Command Promt*.

The term *enabling* above refers to launching [*Visual Studio Installer*](https://visualstudio.microsoft.com/thank-you-downloading-visual-studio/?sku=Community&rel=15), clicking on *Modify* for your installed or yet to be installed *Visual Studio* version and clicking some checkboxes and applying by clicking *Modify*.

Tested on

```
Microsoft Visual Studio Community 2017
Version 15.9.9
VisualStudio.15.Release/15.9.9+28307.518
v14.16 latest v141 tools
Installed Version: Community
Microsoft Visual C++ 2017
Microsoft (R) C/C++ Optimizing Compiler Version 19.16.27027.1
```

It is impossible to do this process in WSL (POSIX) as MSVC is used for building GLFW for MSW. Windows batch scripts for someone who works everyday on POSIX with decent GNU stack may not invoke frustration, but rather something undescribably much more.

## Building

Navigate to this directory in *Developer Command Promt* and execute script

```bat
build_dependencies-msw_msvc2017.bat
```
