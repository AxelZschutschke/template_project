# Valgrind {#Valgrind}

[TOC]

# Overview

Valgrind is not a single tool but contains a complete tool suite for detecting memory management and threading bugs. It
is developed by ["a loose knit group of developers"](https://valgrind.org/info/developers.html) and is available under 
the GNU general public license V2.0 as open source software.

## Get Valgrind

Get it from your OS's package store, most Linux distributions have valgrind available, e.g. via `apt install valgrind`.

Alternatively, valgrind can be built from source using the [git repository](git://sourceware.org/git/valgrind.git)

To build the cloned code, follow the instructions in the README file that the clone should give you. Alternatively, the following should work:
~~~~~.bash
cd valgrind
./autogen.sh
./configure --prefix=...
make
make install
~~~~~

## Using Valgrind

As mentioned before, valgrind contains a set of tools to examine the binaries in a dynamic manner. *dynamic* means, that
the code is actually executed for the test. Valgrind sets up a modified execution environment simulating certain CPU
features and memory. Thus, the execution via valgrind is considerably slower than the original executable and may
allocate more memory. For big projects, it may be beneficial to deconstruct the binary into smaller chunks for
examination.

The individual tools are described in the following.

## Memcheck

Memcheck, a tools for examining the memory allocation, deallocation and initialization process of the executable. It
finds uninitialized variables used e.g. for conditions, buffer overflows, memory leaks etc.

To execute memcheck, issue the following command:

~~~~~.bash
valgrind --tool=memcheck --trace-children=yes --leak-check=full --track-origins=yes --suppressions=<file> <program>
~~~~~

Here, some options are passed to valgrind already, to follow child threads of the main process (`trace-children`), track
the origin of error and leaks (`track-origin`) and perform extended checks for memory leaks (`leak-check`). The option
`tool=memcheck` may be skipped, as it is the default option.

Valgrind can use a suppressions file to suppress known issues and false-positives. This file can be created during an
initial execution with the option `--gen-suppressions=<file>`.

Valgrind also supports an xml output, which can be parsed by different dashboard tools, e.g. by a jenkins plugin (which
is a little buggy, though).

## Cachegrind

Cachegrind is a cache profiler. It performs detailed simulation of the I1, D1 and L2 caches in your CPU and so can
accurately pinpoint the sources of cache misses in your code. It identifies the number of cache misses, memory
references and instructions executed for each line of source code, with per-function, per-module and whole-program
summaries. It is useful with programs written in any language. Cachegrind runs programs about 20--100x slower than
normal.

It is usable for very small examples only, as the caching behavior gets blurred by too many different memory requests.

~~~~~.bash
valgrind --tool=cachegrind --trace-children=yes <program>
~~~~~

## Callgrind 

Callgrind, by Josef Weidendorfer, is an extension to Cachegrind. It provides all the information that Cachegrind does,
plus extra information about callgraphs. It was folded into the main Valgrind distribution in version 3.2.0. Available
separately is an amazing visualisation tool, **KCachegrind**, which gives a much better overview of the data that Callgrind
collects; it can also be used to visualise Cachegrind's output.

~~~~~.bash
valgrind --tool=callgrind --trace-children=yes --callgrind-out-file=<file> <program>
kcachegrind <file>
~~~~~

## Massiv

Massif is a heap profiler. It performs detailed heap profiling by taking regular snapshots of a program's heap. It
produces a graph showing heap usage over time, including information about which parts of the program are responsible
for the most memory allocations. The graph is supplemented by a text or HTML file that includes more information for
determining where the most memory is being allocated. Massif runs programs about 20x slower than normal.

**ms\_print** may be used to analyze the outfile of the massif tool (which is hard to read by humans).

~~~~~.bash
valgrind --tool=massif --trace-children=yes --massif-out-file=<file> <program>
ms_print <outfile>
~~~~~

## Helgrind

Helgrind is a thread debugger which finds data races in multithreaded programs. It looks for memory locations which are
accessed by more than one (POSIX p-)thread, but for which no consistently used (pthread\_mutex_) lock can be found. Such
locations are indicative of missing synchronisation between threads, and could cause hard-to-find timing-dependent
problems. It is useful for any program that uses pthreads. It is a somewhat experimental tool, so your feedback is
especially welcome here.

~~~~~.bash
valgrind --tool=helgrind --trace-children=yes <program>
~~~~~

## Other Tools 

For other contained tools in the valgrind suite, please refer to the 
[project website](https://valgrind.org/info/tools.html)
