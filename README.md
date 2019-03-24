# OpenGL ES Demos for bare Linux framebuffer on ARM SoCs natively

No gears.

## What?

These domos were created inhouse in order to test [OpenGL ES](https://en.wikipedia.org/wiki/OpenGL_ES) on top of [EGL](https://en.wikipedia.org/wiki/EGL_(API)) interface on SoC's that have [Utgard - Mali-400 series](https://en.wikipedia.org/wiki/Mali_(GPU)) GPUs and [Mali](https://en.wikipedia.org/wiki/Mali_(GPU)) driver whilst running on [Linux framebuffer](https://en.wikipedia.org/wiki/Linux_framebuffer) natively (no pbuffer).

No *wayland*, no *Xlib*, no *DirectFB*, no *DRM*. Just *EGL* & *GLES* on *FBDev* within bare terminal.

PoC was demanded for [Allwiner's Utgard - Mali-400 series](http://linux-sunxi.org/Mali#Utgard_.28Mali-400_and_Mali-450.29) thus demos are written for it (GLES2).

## Why?

An [Allwinner H3](http://linux-sunxi.org/H3) based board [Orange Pi Lite](http://www.orangepi.org/orangepilite/) w/ 512MB DDR3 SDRAM costing $12 was given which includes *Mali400MP2* GPU, [sun8i](https://github.com/torvalds/linux/blob/master/arch/arm/boot/dts/sun8i-h3.dtsi) device tree. A question was asked - is it possible to create *OpenGL ES* application that runs directly on *H3* without any desktop environment on mainline kernel and if yes, what would be framerate for FHD output on this board? It coincided with another project where low-cost Alwinner's were evaluated for realtime (simple ^_^) graphics. Somehow it resulted in creating these demos.

Again, that does not mean that this demo won't run on other SoCs (at least, it probably should on all *Allwinner* /w *Utgard* SoCs that can work with *Mali* drivers mentioned below).

## Drivers

In case of *Allwinner* SoCs, you need working

* [Mali loadable kernel driver](https://github.com/mripard/sunxi-mali)
* [Mali userspace library](https://github.com/bootlin/mali-blobs)

See notes below about kernel used.

## Building and running on SoC

### Obviously

Log into your SoC as `root`

```sh
git clone thisrepo && cd thisrepo
```

### About dependencies

Dependencies are divided between stuff that is for SoC (main target) and additions that are needed to build project on devbenches.

* `<project_name>/dependencies/shared/` holds core dependency *Hela*. `code` does not run without it as it inherits it. Note that *Hela* also has one submodule *spdlog* to make life easier.

* `<project_name>/dependencies/shared/` also holds other dependencies, that are needed for `code` to run, for example *GLM*, *stb* a.o. helpers go there.

* `<project_name>/dependencies/devbenches/<os>/` holds all dependencies that are needed on top of *shared* in order to work on and compile project on desktop (x64) OSes. Probably only deps that go in there are are *GLFW* and *GLAD*, see notes further below.

#### Project description (per project)

Each project should have brief description of what it does `<project_name>/README.md`.

#### Download dependencies (per project)

See if *README* in project dependencies directory exists (`<project_name>/dependencies/README.md`) for some extra instructions, for example `HelloFBdev/dependencies/README.md`.

For SoC to get all dependencies for a it should be as simple as executing

```sh
bash <project_name>/dependencies/shared/download_shared_dependencies-posix.sh
```

For *HelloFBdev* that would be

```sh
bash HelloFBdev/dependencies/shared/download_shared_dependencies-posix.sh
```

### Building (per project)

For simplicity build as *root*.

#### Edit `Makefile`

Open and edit `Makefile` for the project you want to build. 

```sh
cd <project_name>/projectfiles/fbdev-allwinner-h3/
<your_favourite_editor> Makefile
```

Change paths to where you have put *Mali* kernel driver and userspace libraries, see `MALIINCLIBDIR` and `MALIINCHEADERDIR` values. And see other notes in `Makefile`.

#### Build

```sh
cd <project_name>/projectfiles/fbdev-allwinner-h3/
make
```

Binary will be placed in the same `<project_name>/projectfiles/fbdev-allwinner-h3/` and is called *gl-test* (see `TARGET` in `Makefile`). It will also copy `assets` directory besides the binary (it may hold textures, shaders, geometries...).

### Running

For simplicity run as *root*.
You can be logged in through SSH and you will be able to run as long the board has display attached to it, however it is best to attach keyboard and mouse to the board for user I/O.

#### Note about raw binary

Possible, but don't run binary `./gl-test` directly. Use one of shell script helpers provided.

`<project_name>/projectfiles/fbdev-allwinner-h3/run.sh` is the suggested, see notes further below.

#### Prep runner scripts

It is in your interests to make all runner bash script helpers in the directory executable.

```sh
cd <project_name>/projectfiles/fbdev-allwinner-h3/
chmod a+x ./*.sh
```

#### Environment variables

Environment variables are used as a way to pass to app information about keyboard and mouse endpoints.
If those variables are not set, app will try to automatically detect keyboard and mouse unless user code has set for project not to use inputs.

If you wish to supply them manually, then use

* `GL_KEYBOARD` as path to keyboard input event  
* `GL_MOUSE` as path to mouse input event

You can query for what values to use by issuing `cat /proc/bus/input/devices`. Look for event handler (`eventN`). Use `/dev/input/eventN`. `ls -la /dev/input/by-id/` will also give hints via `*event-kbd` and `*event-mouse`.

An example result is

```sh
export GL_KEYBOARD=/dev/input/event1
export GL_MOUSE=/dev/input/event0
./run.sh
```

#### Command line arguments

App expects command line arguments. Failing to supply them will make app fall to defaults as set in source. Each project may have different command line arguments available, but two of them are always there

`--width <INT>` for width and `--height <INT>` for height expressed in pixels.

In these demos default size is set 640×480 in user code.

You can query your monitor size by `cat /sys/class/graphics/fb0/virtual_size`

An example output is `1920,3240`. Note that the height should be divided by `(CONFIG_DRM_FBDEV_OVERALLOC/100)`. If kernel was built with `CONFIG_DRM_FBDEV_OVERALLOC=300` height would be `3240/(300/100)=1080`.

Although obviously (hopefully?) you know what your display resolution is, system may sometimes boot up with messed up resolution. If you ask for too big resolution logfile will greet you with message about *EGL* failing to create window surface.

An example result is

```sh
./run.sh --width 1920 --height 1080
```

#### Command line arguments (per project)

For per project custom command line arguments and other notes see each project's README (`<project_name>/README.md`)

#### Putting it all together

For app to detect inputs automatically

```sh
cd <project_name>/projectfiles/fbdev-allwinner-h3/
./run.sh --width 1920 --height 1080
```

to explicitly specify inputs

```
cd <project_name>/projectfiles/fbdev-allwinner-h3/
GL_KEYBOARD=/dev/input/event1 GL_MOUSE=/dev/input/event0 ./run.sh --width 1920 --height 1080
```

#### About different runner scripts

`run.sh` is wrapping binary within [`tput`](http://man7.org/linux/man-pages/man1/tput.1.html), where it cleans and *locks* terminal, hides terminal cursor

```sh
./run.sh --argumentA 1  --argumentB 2
```

`run-helper.sh` is shortcut - it is just used to save argument values (and environment too if needed) and then launching demo can be done by simply issuing

```sh
./run-helper.sh
```

`run-raw.sh` just sets up log file and outputting to log file before running binary, no tput wrapping

```sh
./run-raw.sh --width 1920 --height 1080
```

#### Logging

If runner scripts are used each run cycle is logged in `run.log` which gets created next to binary

```sh
cd <project_name>/projectfiles/fbdev-allwinner-h3/
cat run.log | more
```

## Tested on

* **Allwinner H3, Mali r8p1 driver version, Orange Pi Lite**  
	Status: working  
* **N/A**  
	Status: N/A  
	
## Notes about Allwinner kernel

Most probably you will need to build your own kernel as it needs patches.  
This code was written on and tested while using the latest stable kernel at time when board arrived - `4.20.12`.  
The kernel was cross compiled on Ubuntu x64 (using *Linaro* toolchain). The kernel composition was something like [mainline](https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/?h=v4.20.12) -> [linux-sunxi/sunxi-next](https://github.com/linux-sunxi/linux-sunxi/tree/sunxi-next) -> [megous/linux](https://github.com/megous/linux) (for H3 patches) -> manual patches (notably `CONFIG_DRM_FBDEV_OVERALLOC` and `CONFIG_DRM_FBDEV_LEAK_PHYS_SMEM`).  
GNU stack comes via [Armbian](https://www.armbian.com) (*server* variation obviously, as only terminal is needed) + manual boot argument patches.  

The mentioned *Mali* loadable kernel object was built against kernel headers, *lima* unloaded, *mali* loaded.

*Allwinner H3* becomes hot, very hot. This is why [megous/linux](https://github.com/megous/linux) step was used while building the kernel - Ondřej Jirman has tried to [address this issue](http://linux-sunxi.org/Template:H3_Support_status#Mainline_kernel).

## Other notes

Waiting for cheap 4th generation or newer *Midgard*'s (*GLES 3.2*) on ūbercheap SoCs. Fine, 1st to 3rd generation (*GLES 3.1*) will also do. And drivers.

`cat /dev/urandom > /dev/fb0`
