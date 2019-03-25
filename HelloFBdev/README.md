# Hello FBdev

## About

A triangle is a polygon with three edges and three vertices. It is one of the basic shapes in geometry. [[1]](https://en.wikipedia.org/wiki/Triangle)

## Building on SoC

See this repo root readme which should explain steps to build on SoC in detail.

* `dependencies/shared/download_shared_dependencies-posix.sh`
* `cd projectfiles/fbdev-<soc_name>`
* Edit `Makefile`
* `make`
* `./run.sh --width 1920 --height 1080`

## Command line arguments

`--width <INT>` for width expressed in pixels  
`--height <INT>` for height expressed in pixels  

```sh
./run.sh --width 1920 --height 1080
```

## User input controls

None, no need to specify. Input device usage is deliberately disabled in project code.

`SIGINT` (`Control+C`) or `SIGQUIT` (`Control+\`)  to exit.

## Building on devbench

* See this repo root readme which should explain steps.
* Refer to `dependencies/devbenches/<devbench_os>/README.md`
* Refer to `projectfiles/<devbench_os>/README.md`

### Try automated

#### macOS

```sh
cd <this_directory>
bash dependencies/shared/download_shared_dependencies-posix.sh
bash dependencies/devbenches/macos-clang/build_dependencies-macos_clang.sh
bash projectfiles/desktop-macos-clang-xcode/HelloFBdev.sh
open projectfiles/desktop-macos-clang-xcode/Build
```
See contents of `Debug` or `Release`.
