# CMake {#CMake}

[TOC]

# Overview 

CMake is a cross-platform build system configuration tool developed by KitWare and released under a BSD-3 type open
source license. 

Building project sources into executable code usually is done using a build chain, which configures, builds, tests and
packages the project. These steps can be orchestrated using CMake. This only is the most basic step of a modern CI
chain, the build on a single host / platform. Usually, several individual of such builds with different configurations
need to be carried out, which is *NOT* the scope of CMake - refer to configuration management and continuous integration
tools for this.

## Get CMake

Get it from your OS's package store, most Linux distributions have CMake available, e.g. via `apt install cmake`.

One may get CMake as source distribution as well as [git repository](https://github.com/Kitware/CMake), follow the
projects build instructions. Hint: it may be easier to build a current CMake version using your OS's dated version, see
[building CMake with CMake](https://github.com/Kitware/CMake#building-cmake-with-cmake) on the projects own readme.

**ccmake** For debian-based projects use the *cmake-curses-gui* package, or build cmake manually with more current
version, enable the curses gui via configure.

## Enable CMake

CMake projects contain one (or more) *CMakeLists.txt* files, describing build targets and dependencies. Refer to
this projects *CMakeLists.txt* as a reference. It allows for non-code target, e.g. the Doxygen target used for
generating documentation and is able to automatically build and use external projects as dependencies. This becomes
trivial for git-hosted cmake-configured dependencies, which CMake is able to build and use out-of-the-box, e.g.
see the *googletest* target of this project.

## Use CMake

The easiest way to use CMake in a CMake configured project is by installing a CMake GUI, which is available as
curses based terminal version and as QT based app (the latter is a pro-tip for Windows builds). CMake automatically
performs a configuration run, make sure your compiler can be found. You may help CMake by specifying certain environment
variables, e.g. `CC=/usr/bin/clang` if you intend to use a different-than-standard compiler.

Changes to the current project configuration can be performed by specifying parameters on the command line, e.g. `cmake
<src-dir> -DDOXYGEN=ON`, which would enable an option switch in the config. This can be done graphically using either
the curses or QT GUI as well. Installation paths may be specified like that as well.

CMake encourages out-of-source builds, which also makes live easier with version control systems, as the source folder
stays clean during build an no build artifacts are created therein. For this create a build folder outside of the
project (or ignore a certain folder via *.gitignore* for example). From this folder perform `cmake <src-folder>
<options>` and watch CMake configuring the project. It will inform about problems. If everything works, then `cmake
--build . [--target X]` will build the project. 
