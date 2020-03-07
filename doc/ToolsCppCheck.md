# CppCheck {#CppCheck}

[TOC]

# Overview

CppCheck is a static code analysis tool for C/C++ code, providing support by automating parts of the code review
process.  It is developed under GNU general public license V3.0. 

## Get CppCheck

Get it from your OS's package store, most Linux distributions have CppCheck available, e.g. via `apt install cppcheck`.

Alternatively, the tool can be build manually from its [repository](https://github.com/danmar/cppcheck.git), following
the build instructions. 

## Using CppCheck

CppCheck works best beeing run on cpp (implementation) files, and has some issues with header only projects. Here, test
code can help to include the source code into the analysis.

With
~~~~~.cmake
option( CPPCHECK           "Enable cppcheck"           OFF)
...
if( CPPCHECK )
  find_program( CPPCHECK_EXECUTABLE NAMES cppcheck )

  if( CPPCHECK_EXECUTABLE )
    file(GLOB CPPCHECK_IN 
      ${CMAKE_CURRENT_SOURCE_DIR}/include/* 
      ${CMAKE_CURRENT_SOURCE_DIR}/src/* 
      ${CMAKE_CURRENT_SOURCE_DIR}/test/unit/* 
      ${CMAKE_CURRENT_SOURCE_DIR}/test/api/* 
    )
    set(CPPCHECK_INCLUDE_DIRS 
      -I${CMAKE_CURRENT_SOURCE_DIR}
      -I${CMAKE_CURRENT_SOURCE_DIR}/include 
      -I${CMAKE_CURRENT_SOURCE_DIR}/vendor 
      -I${CMAKE_CURRENT_SOURCE_DIR}/test/api/*
    )

    set(CPPCHECK_OPTIONS 
      --xml 
      --language=c++ 
      --std=c++14 
      --enable=all 
      --inconclusive )
    set(CPPCHECK_OUT 
      --output-file=${CMAKE_CURRENT_BINARY_DIR}/cppcheck.xml )

    add_custom_target( cppcheck ALL
      COMMAND ${CPPCHECK_EXECUTABLE} 
        ${CPPCHECK_OUT} 
        ${CPPCHECK_OPTIONS} 
        ${CPPCHECK_INCLUDE_DIRS} 
        ${CPPCHECK_IN}
      COMMENT "Running cppcheck"
      VERBATIM )
  else()
    message( "cppcheck need to be installed to generate the cppcheck report" )
  endif()
endif()
~~~~~

if ( DOXYGEN )
  # check if Doxygen is installed
  find_package(Doxygen)
  if (DOXYGEN_FOUND)
    # set input and output files
    set( DOXYGEN_IN 
      ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in)
    set( DOXYGEN_OUT 
      ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT})

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc ALL
      COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Generating API documentation with Doxygen"
      VERBATIM )
  else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
  endif (DOXYGEN_FOUND)
endif( DOXYGEN )
