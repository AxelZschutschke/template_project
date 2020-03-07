# CCCC {#CCCC}

[TOC]

# Overview

CCCC, the *C and C++ Code Counter* is a tool for measuring and reporting code metrics. It is released as a result of a
PhD thesis by Tim Littlefair and under the GNU general public license V2.0.

## Get CCCC

Get it from your OS's package store, most Linux distributions have CCCC available, e.g. via `apt install cccc`.

Alternatively, the tool can be build manually from its [website](http://sourceforge.net/projects/cccc), following
the build instructions. 

## Using CCCC

Using CCCC is pretty much straight forward. The tool generates a HTML output containing all relevant code metrics and
documentation about the metrics and how they are calculated. The tool mainly needs to get all the sources and include
directories presented to work properly. 

~~~~~.cmake
option( CCCC           "Enable cccc metrics"           OFF)
if( CCCC )
  find_program( CCCC_EXECUTABLE NAMES cccc )
  if( CCCC_EXECUTABLE )
    file(GLOB CCCC_IN 
      ${CMAKE_CURRENT_SOURCE_DIR} )
    set(CCCC_INCLUDE_DIRS 
      -I${CMAKE_CURRENT_SOURCE_DIR} 
      -I${CMAKE_CURRENT_SOURCE_DIR}/test/api
      -I${CMAKE_CURRENT_SOURCE_DIR}/include 
      -I${CMAKE_CURRENT_SOURCE_DIR}/vendor 
      -I${CMAKE_CURRENT_SOURCE_DIR}/examples )
    set(CCCC_OPTIONS  
      --lang=c++ )
    set(CCCC_OUT 
      --outdir=${CMAKE_CURRENT_BINARY_DIR}/cccc 
      --html_outfile=${CMAKE_CURRENT_BINARY_DIR}/cccc/cccc.html )
    add_custom_target( cccc ALL
      COMMAND ${CCCC_EXECUTABLE} ${CCCC_OUT} ${CCCC_OPTIONS} ${CCCC_INCLUDE_DIRS} ${CCCC_IN}
      COMMENT "Running cccc"
      VERBATIM )
  else()
    message( "cccc need to be installed to generate the cccc report" )
  endif()
endif()
~~~~~
