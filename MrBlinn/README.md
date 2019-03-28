# Mr Blinn

## About

James F. Blinn (born 1949) is an American computer scientist who first became widely known for his work as a computer graphics expert at NASA's Jet Propulsion Laboratory (JPL), particularly his work on the pre-encounter animations for the Voyager project, his work on the Carl Sagan documentary series Cosmos, and the research of the Blinn–Phong shading model. [1](https://en.wikipedia.org/wiki/Jim_Blinn)

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

Code in this test uses offscreen render target, you can set size for that  
`--buffw <INT>` for width expressed in pixels  
`--buffh <INT>` for height expressed in pixels  

Thus for example on FHD monitor you could draw full monitor size, but actually upscaled HD rendering. FPS will profit.

```sh
./run.sh --width 1920 --height 1080 --buffw 1280 --buffw 720
```

### User input controls

#### Mouse

* Move: to look
* Scroll wheel: change field of view
	
#### Keyboard

* esc: exit
* w: move forward
* a: strafe left
* s: move backward
* d: move right
* space: up
* ctrl: down

* arrows: look up/left/down/right (fallback for when no mouse available)

* undef: toggle shadows (default on)
* undef: toggle parallax occlusion mapping (default on)
* undef: toggle steep self shadowing (default on)
* undef: toggle SSAO (default on)
* undef: toggle FXAA (default on)

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


## About test

* This uses *VAO*, *EBO* *VBO*
* Test geometries used are manually written to test striding
* Testing textures and sRGB (namely, lack of sRGB on Allwinner and thus manual LUTing before offload to GPU)
* Everything in LDR, no float targets
* Naive Blinn-Phong reflection model
* It is not Mr Blinn's fault he's coming from Murica, but unfortunatelly no energy conservation in this test (no attempt for PBR whatsoever)
* Testing offscreen render target
* Testing renderbuffer
* Testing 24bit depth in renderbuffer
* Testing 24bit depth in framebuffer
* Testing cube map
* MSAA not used thus no blitting tested
* Some features to substantiate offscreen buffer thrown on top
	* Using 24bit depth for shadows calculations
	* PCF shadows for one point light [2]
	* Parallax occlusion mapping (iterations used to stress GPU) [2]
	* Parallax steep self shadowing (iterations used to stress GPU) [2]
	* SSAO implementation using 24bit depth buffer, not Gbuffer [2]
	* FXAA

Some notes

* Allwinner Mali implementation does not load `OES_texture_float` and `OES_texture_float_linear`.
* Allwinner Mali implementation does not have `glDrawArraysInstancedEXT` and `glDrawElementsInstancedEXT`.