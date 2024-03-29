# Hello FBdev

## About

A triangle is a polygon with three edges and three vertices. It is one of the basic shapes in geometry. [[1]](https://en.wikipedia.org/wiki/Triangle)

## Building on SoC

See this repo root readme which should explain steps to build on SoC in detail.

### TL;DR

* `bash dependencies/shared/download_shared_dependencies-posix.sh`
* `cd projectfiles/fbdev-<soc_name>`
* `<your_favourite_editor_to_edit> Makefile`
* change `MALIINCLIBDIR` and `MALIINCHEADERDIR`
* `make`
* `bash run.sh --width 1920 --height 1080`

### Command line arguments

`--width <INT>` for width expressed in pixels  
`--height <INT>` for height expressed in pixels  

```sh
./run.sh --width 1920 --height 1080
```

### User input controls

None, no need to specify. Input device usage is deliberately disabled in project code.

`SIGINT` (`Control+C`) or `SIGQUIT` (`Control+\`)  to exit.

## Building on devbenches

* See this repo root readme which should explain structure
* Refer to `dependencies/README.md` about dependencies
* Refer to `dependencies/shared/` to get shared deps
* Refer to `dependencies/devbenches/<devbench_os>/README.md` to build devbench deps
* Refer to `projectfiles/<devbench_os>/README.md` to build project

### Feeling lucky?

It is possibe that all devtools needed are already on your machine.

#### MSW MSVC

Fire up *Developer Command Promt*

```bat
cd <this_directory>
call dependencies\shared\download_shared_dependencies-msw.bat
call dependencies\devbenches\msw-msvc\build_dependencies-msw_msvc2017.bat
call projectfiles\desktop-msw-msvc2017-vs\HelloFBdev.bat
start projectfiles\desktop-msw-msvc2017-vs\Build
```

See contents of `x64` or `x86`.

#### macOS Clang

Fire up *Terminal*

```sh
cd <this_directory>
bash dependencies/shared/download_shared_dependencies-posix.sh
bash dependencies/devbenches/macos-clang/build_dependencies-macos_clang.sh
bash projectfiles/desktop-macos-clang-xcode/HelloFBdev.sh
open projectfiles/desktop-macos-clang-xcode/Build
```

See contents of `Debug` or `Release`.
