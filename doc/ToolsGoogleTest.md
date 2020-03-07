# GoogleTest {#GoogleTest}

[TOC]

# Overview 

GTest and GMock are a c/c++ testing and mocking framework respectively, actively developed and maintained by Google
and released under a BSD-3 clause open source license.

Formerly both project have been developed separately, but have been merged to *googletest* now. GTest can be used
in a header-only manner, while GMock needs some runtime libraries to be linked against the test executables.

## Get GoogleTest

Get it from your OS's package store, most Linux distributions have GoogleTest available, e.g. via `apt install
googletest`. 

One may get GoogleTest as source distribution as well as [git repository](https://github.com/google/googletest),
follow the build instructions of the libraries. Here, GoogleTest is downloaded, build and used during project
generation automatically, using the CMake ExternalProject module. See the main *CMakeLists.txt* file:

~~~~~.cmake
option( COMPILE_TESTS      "Enable tests"              ON)

include(ExternalProject)

...
if (COMPILE_TESTS)
    ... 
    ExternalProject_Add( googletest
      GIT_REPOSITORY https://github.com/google/googletest.git
      PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
      INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}
      CMAKE_ARGS 
        -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/gtest 
        -DBUILD_SHARED_LIBS=ON
      )
~~~~~


## Set up CMake Project

For using GoogleTest from a CMake project, test cases / test runner executables need to be defined and backed with
source code. Each of the tests is build into and executable and linked against gtest, gmock and other relevant
libraries (also the projects target libraries if applicable).

When adding the test to ctest via `add_test()`, the tests will be executed and evaluated automatically with a ctest run.
Add a command line option for specifying an test report format, e.g. `--gtest_output="xml:file.xml"`.

~~~~~.cmake
option( COMPILE_TESTS      "Enable tests"              ON)

...
if (COMPILE_TESTS)
    file( GLOB GTEST_FILES test/unit/*)
    foreach( FILENAME ${GTEST_FILES} )
      get_filename_component( TESTNAME ${FILENAME} NAME_WE )
      link_directories( ${CMAKE_CURRENT_BINARY_DIR}/gtest/lib )
      add_executable(  ${TESTNAME} ${FILENAME} )
      add_dependencies( ${TESTNAME} googletest )
      target_include_directories( ${TESTNAME} 
        PRIVATE 
          ${CMAKE_CURRENT_BINARY_DIR}/gtest/include 
        )
      target_link_libraries( ${TESTNAME} 
        gtest 
        gmock )
      add_test( NAME ${TESTNAME} 
        COMMAND ${TESTNAME} --gtest_output="xml:${TESTPATH}_gtest.xml")
    endforeach()
endif ()
~~~~~

## Creating Tests with GTest

## Creating Fakes with GMock

