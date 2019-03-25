# Project dependencies

## Downloading dependencies for SoC

Use `bash shared/download_shared_dependencies-posix.sh`

It will download all dependencies to build and run this project on SoC, namely it will download *Hela* and place in `shared/hela/` as well as any extras and place them in `shared/extraname/`.

## Downloading dependencies for devbenches

If you also want to compile the project on x64 devbench, then first you have to download shared dependencies

* `bash shared/download_shared_dependencies-posix.sh` for POSIX shell
* `shared/download_shared_dependencies-msw.bat` for MSW via *Developer Command Promt* (POSIX variant should work on WSL)

and then navigate to `devbenches/<devbench_os>/` where you should find *README* and/or sript that will download and build GLFW and GLAD for the specific OS.

## Next

Proceed to project building.

